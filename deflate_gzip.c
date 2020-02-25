#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
//gcc -o zlibtest deflate_gzip.c.c -lz
//sudo apt-get install zlib1g zlib1g-dev zlibc


 //https://www.cnblogs.com/yanghaizhou/p/5268692.html 
 /*
 网上有很多针对zlib的总结，但是很零散，自己经过总结，实现了用zlib压缩一个文件为gzip格式，似的可以直接使用winr工具解压。

具体方法是使用zlib的deflate系列函数，将buffer压缩为gzip格式，deflateInit2的参数注意使用MAX_WBITS+16，这样压缩后可以带gzip的头、尾信息。

然后将压缩后的内容直接写入到目标文件，保存为.gz， 使用WinR就可以直接解压了。

demo程序如下(deflate_gzip.c)：
 */
/*******************************************************************************
* Compress gzip data
* @parm[data] data buffer to be compressed
* @parm[dlen] data buffer length
* @parm[zdata] data buffer to save the compressed datas
* @parm[zdlen] compressed data buffer length
* return: 0 - OK; -1 - FAIL 
*******************************************************************************/ 
int gzcompress(Bytef *data, uLong dlen, Bytef *zdata, uLong *zdlen)
{
    int err = 0;
    z_stream c_stream;
    
    printf("%s: data=%p, dlen=%lu, zdata=%p, *zdlen=%lu\n",
        __func__, data, dlen, zdata, *zdlen);
    
    if(data && dlen > 0) 
    {
        c_stream.zalloc = NULL;
        c_stream.zfree = NULL;
        c_stream.opaque = NULL;
        //use parm 'MAX_WBITS+16' so that gzip headers are contained
        if(deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
            MAX_WBITS + 16, 8, Z_DEFAULT_STRATEGY) != Z_OK) 
        {
            printf("%s: deflateinit2 failed!\n",__func__);
            return -1;
        }
        c_stream.next_in  = data;
        c_stream.avail_in  = dlen;
        c_stream.next_out = zdata;
        c_stream.avail_out  = *zdlen;
        while(c_stream.avail_in != 0 && c_stream.total_out < *zdlen)
        {
            if(deflate(&c_stream, Z_NO_FLUSH) != Z_OK) {
                printf("%s: deflate failed!\n",__func__);
                return -1;
            }
        }
        if(c_stream.avail_in != 0) {
            printf("%s: avail_in not zero!\n",__func__);
            return c_stream.avail_in;
        }
        for(;;) 
        {
            if((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END)
                break;
            if(err != Z_OK) {
                printf("%s: deflate finish fail: %d\n",__func__, err);
                return -1;
            }
        }
        if(deflateEnd(&c_stream) != Z_OK) {
            printf("%s: deflate end failed!\n",__func__);
            return -1;
        }
        *zdlen = c_stream.total_out;
        return 0;
    }
    return -1;
}

/*******************************************************************************
* Compress a file into a gzip file
* @parm[input_name] the file path to be compressed
* @parm[output_name] output path of compressed gzip file
* return: 0 - OK; -1 - FAIL 
*******************************************************************************/ 
int compress_file_to_gzip(char * input_name, char * output_name)
{
    FILE *fp = NULL;
    uLong flen, clen;
    unsigned char * fbuf = NULL;
    unsigned char * cbuf = NULL;
    char def_output_name[PATH_MAX] = {0};    

    if((fp = fopen(input_name, "rb")) == NULL)
    {
        printf("%s: can not open %s!\n", __func__, input_name);
        return -1;
    }
    
    /*load file content to buffer*/
    fseek(fp, 0L, SEEK_END);
    flen = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    fbuf = (unsigned char *)malloc(flen * sizeof(unsigned char));
    if(NULL == fbuf){
        printf("%s: no enough memory!\n", __func__);
        goto __error;
    }
    fread(fbuf, sizeof(unsigned char), flen, fp);
    fclose(fp);
    fp = NULL;
    
    /*compute compressBound*/
    clen = compressBound(flen);
    cbuf = (unsigned char *)malloc(clen * sizeof(unsigned char));
    if(NULL == cbuf) {
        printf("%s: no enough memory!\n", __func__);
        goto __error;
    }
    
    if(gzcompress(fbuf, flen, cbuf, &clen))
    {
        printf("%s: compress %s failed!\n", __func__, input_name);
        goto __error;
    }

    if(NULL == output_name) {
        snprintf(def_output_name, sizeof(def_output_name),
        "%s.gz", input_name);
        output_name = def_output_name;
    }
    if((fp = fopen(output_name, "wb")) == NULL)
    {
        printf("%s: can not open %s!\n", __func__, output_name);
        goto __error;
    }
    fwrite(cbuf, sizeof(unsigned char), clen, fp);
    
    fclose(fp);
    free(fbuf);
    free(cbuf);
    return 0;

__error:
    if(fp) fclose(fp);
    if(fbuf) free(fbuf);
    if(cbuf) free(cbuf);
    return -1;
}

int main(int argc, char * argv[])
{
    if(argc < 2) {
        printf("too few args!\n");
        return 0;
    }

    if(argc < 3) {
        return compress_file_to_gzip(argv[1],NULL);
    }

    return compress_file_to_gzip(argv[1], argv[2]);
}
