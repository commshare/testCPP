/*
go web 编程
XML本质上是一种树形的数据格式，而我们可以定义与之匹配的go 语言的 struct类型，然后通过xml.Unmarshal来将xml中的数据
解析成对应的struct对象。

*/
package main

import (
	"encoding/xml"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"strings"
)

/*是struct的一个特性，它们被称为 struct tag，它们是用来
辅助反射的*/
type Recurlyservers struct {
	XMLName     xml.Name `xml:"servers"` //struct中有一个叫做XMLName，且类型为xml.Name字段，那么在解析的时候就会保存这个element的名字到该字段,如上面例子中的servers。
	Version     string   `xml:"version,attr"`
	Svs         []server `xml:"server"`
	Description string   `xml:",innerxml"` //如果struct的一个字段是string或者[]byte类型且它的tag含有 ",innerxml" ， Unmarshal将会将此字段所对应的元素内所有内嵌的原始xml累加到此字段上，如上面例子Description定义。
}
type server struct {
	XMLName    xml.Name `xml:"server"`
	ServerName string   `xml:"serverName"`
	ServerIP   string   `xml:"serverIP"`
}

/*http://blog.studygolang.com/2012/12/%E6%A0%87%E5%87%86%E5%BA%93-xml%E5%A4%84%E7%90%86%EF%BC%88%E4%B8%80%EF%BC%89/*/
func TestXml() {

	var t xml.Token
	var err error

	input := `<Person><FirstName>Xu</FirstName><LastName>Xinhua</LastName></Person>`
	inputReader := strings.NewReader(input)

	// 从文件读取，如可以如下：
	// content, err := ioutil.ReadFile("studygolang.xml")
	// decoder := xml.NewDecoder(bytes.NewBuffer(content))

	decoder := xml.NewDecoder(inputReader)
	for t, err = decoder.Token(); err == nil; t, err = decoder.Token() {
		switch token := t.(type) {
		// 处理元素开始（标签）
		case xml.StartElement:
			name := token.Name.Local
			fmt.Printf("Token name: %s\n", name)
			for _, attr := range token.Attr {
				attrName := attr.Name.Local
				attrValue := attr.Value
				fmt.Printf("An attribute is: %s %s\n", attrName, attrValue)
			}
		// 处理元素结束（标签）
		case xml.EndElement:
			fmt.Printf("Token of '%s' end\n", token.Name.Local)
		// 处理字符数据（这里就是元素的文本）
		case xml.CharData:
			content := string([]byte(token))
			fmt.Printf("This is the content: %v\n", content)
		default:
			// ...
		}
	}

}

func main() {
	/*打开一个文件*/
	file, err := os.Open("servers.xml") // For read access.
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	/*这个是因为上面的代码文件打开ok，如果下面的失败，那么要执行这个close*/
	defer file.Close()
	/*数据一次性都读取出来？ data是一个[]byte*/
	data, err := ioutil.ReadAll(file)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	v := Recurlyservers{} /*这个v是空的吧，是赋值为空值？*/
	/*func Unmarshal(data []byte, v interface{}) error*/
	/*xml即系后存到v里,传递是v是引用*/
	err = xml.Unmarshal(data, &v)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	/*打印v*/
	fmt.Println(v)
	TestXml()
	parseStudyGo()
}

/*
$ ./test_go_parse_xml.exe
{{ servers} 1 [{{ server} Shanghai_VPN 127.0.0.1} {{ server} Beijing_VPN 127.0.0.2}]

//如果struct的一个字段是string或者[]byte类型且它的tag含有 ",innerxml" ， Unmarshal将会将此字段所对应的元素内所有内
//嵌的原始xml累加到此字段上，如上面例子Description定义。
<server>
<serverName>Shanghai_VPN</serverName>
<serverIP>127.0.0.1</serverIP>
</server>
<server>
<serverName>Beijing_VPN</serverName>
<serverIP>127.0.0.2</serverIP>
</server>
}


Token name: Person
Token name: FirstName
This is the content: Xu
Token of 'FirstName' end
Token name: LastName
This is the content: Xinhua
Token of 'LastName' end
Token of 'Person' end

*/
/*解析xml到一个结构体
这里的解析没有用到任何tag。元素首字母的大小写不能错。
*/
type Result struct {
	Person []Person /*数组*/
}
type Person struct {
	Name      string
	Age       int
	Career    string
	Interests Interests
}
type Interests struct {
	Interest []string /*Interest只是一个普通的string，由于是多个，因而是一个string slice， 个数不确定的，这个是个string slice*/
}

func parseStudyGo() {
	content, err := ioutil.ReadFile("studygo.xml")
	if err != nil {
		log.Fatal(err)
	}
	var result Result /*直接填充到result里？*/
	err = xml.Unmarshal(content, &result)
	if err != nil {
		log.Fatal(err)
	}
	/*2017/04/24 15:32:08 {[{polaris 28 无业游民 {[编程 下棋]}} {studygolang 27 码农 {[编程 下棋]}}]}*/
	log.Println(result) /*reslut是person类型的数组*/
}

/*
 {  //数组
 	[  //数组


    {  //数组元素1
        polaris
        28
        无业游民
        { //数组
               [编程 下棋]  //数组元素
        }

    }

    {  //数组元素2
        studygolang
        27
        码农
        {  //数组
           [编程 下棋]  //数组元素
        }
    }


    ]


 }


*/
