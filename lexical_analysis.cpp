#include<iostream>
#include<string>
#include<windows.h>
#include<cstdio>
#include<fstream>
#include<vector>
using namespace std;
int line_count,keyword_count,separator_count,operator_count,identifier_count,num_count,char_count;//行数，各类单词总数，字符总数
int state;//自动机状态
//关键字、运算符、分隔符
string KEYWORD[32]={"int","char","long","double","void","enum","float","short","signed","unsigned","struct","union",/*数据类型*/
                    "while","for","do","if","else","continue","break","return","switch","case","default","goto",/*控制语句*/
                    "typedef","const","sizeof","volatile","auto","extern","register","static"/*复杂类型关键字*/};//关键字
char OPERATOR[13]={'+','-','*','/','=','<','>','!','%','&','|','!','?'};//运算符
char SEPARATOR[11]={';','(',')','{','}','[',']','\'','\"',',','.'};//分隔符
vector<string> err;
class analysis//词法分析类
{
public:
    int forward;//字符指针，向前指针
    int Judge_Keyword(string &a)//判断是否是关键字
    {
        for(int j=0;j<32;j++)
        {
            if(a==KEYWORD[j])
            {
                return j;
            }
        }
        return (-1);
    }
    char get_char(string& ab,char c)//根据字符指针读入下一个字符
    {
        if(forward==ab.size())
            return c;
        c=ab.at(forward);
        forward++;
        return c;
    }///*
    char get_nbc(string& ab,char c)//跳过空格
    {
        while(c==' '||c=='\t')
        {
            //
            c=get_char(ab,c);
            if(forward==ab.size())
            return c;
        }
        return c;
    }
    void ana(string& ab)//构建自动机词法分析
    {
        char c;//当前读入的字符
        string token;//字符数组存放当前正在识别的字符串
        state=0;
        do
        {
            switch(state)
            {
                case 0:
                    //token="";
                    c=get_char(ab,c);
                    c=get_nbc(ab,c);
                    switch(c)
                    {
                        
                        case 'a':
                        case 'b':
                        case 'c':
                        case 'd':
                        case 'e':
                        case 'f':
                        case 'g':
                        case 'h':
                        case 'i':
                        case 'j':
                        case 'k':
                        case 'l':
                        case 'm':
                        case 'n':
                        case 'o':
                        case 'p':
                        case 'q':
                        case 'r':
                        case 's':
                        case 't':
                        case 'u':
                        case 'v':
                        case 'w':
                        case 'x':
                        case 'y':
                        case 'z':
                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D':
                        case 'E':
                        case 'F':
                        case 'G':
                        case 'H':
                        case 'I':
                        case 'J':
                        case 'K':
                        case 'L':
                        case 'M':
                        case 'N':
                        case 'O':
                        case 'P':
                        case 'Q':
                        case 'R':
                        case 'S':
                        case 'T':
                        case 'U':
                        case 'V':
                        case 'W':
                        case 'X':
                        case 'Y':
                        case 'Z': state=1;if(forward==ab.size()){cout << "<IDENTIFIER," << c << '>' << endl;identifier_count++;}break;
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9': state=2;if(forward==ab.size()){cout << "<NUM," << c << '>' << endl;num_count++;}break;
                        case '<': state=8;break;
                        case '>': state=9;break;
                        case ':': state=10;break;
                        case '+': state=11;break;
                        case '-': state=12;break;
                        case '*': state=13;break;
                        case '/': state=14;break;
                        case '&': state=15;break;
                        case '|': state=16;break;
                        case '!': state=17;break;
                        case '=': state=19;break;
                        case '%': state=0;
                                cout << "<OPERATOR," << c << '>' << endl;
                                operator_count++;
                                token="";
                                break; 
                        case '?': state=0;
                                cout << "<OPERATOR," << c << '>' << endl;
                                operator_count++;
                                token="";
                                break;
                        case '(': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case ')': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case '{': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case '}': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case '[': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case ']': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case ';': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case '\"': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case '\'': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case ',': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        case '.': state=0;
                                cout << "<SEPARATOR," << c << '>' << endl;
                                separator_count++;
                                token="";
                                break;
                        
                        case '@':
                        case '$':state=20;break;
                        case '\\':state=21;break;
                        default: state=21;break;
                    };
                    break;
                case 1://标识符状态
                    token+=c;
                    c=get_char(ab,c);
                    
                    if(c>='0'&&c<='9'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_')
                    {
                        state=1;
                        if(forward==ab.size())
                        {
                            token+=c;
                            int jud=Judge_Keyword(token);
                            if(jud!=-1)
                            {
                                cout << "<KEYWORD," << token << '>' << endl;
                                keyword_count++;
                            }
                            else
                            {
                                cout << "<IDENTIFIER," << token << '>' << endl;  
                                identifier_count++;
                            }
                        }
                    }
                    else
                    {
                        forward--;
                        state=0;
                    //？返回符号表的入口指针  
                        if(c=='@'||c=='$')
                        {
                            string errhandle;
                            
                            err.push_back(errhandle);
                        }
                        int jud=Judge_Keyword(token);
                        if(jud!=-1)//关键字
                        {
                            cout << "<KEYWORD," << token << '>' << endl;
                            keyword_count++;
                        }
                        else//为用户自定义标识符
                        {
                            cout << "<IDENTIFIER," << token << '>' << endl;  
                            identifier_count++;
                        }
                        token="";           
                    };
                    break;
                case 2://常数状态
                    token+=c;
                    c=get_char(ab,c);
                    if(forward==ab.size()&&c>='0'&&c<='9')
                    {
                        token+=c;
                        cout << "<NUM," << token << '>' << endl;
                        num_count++;
                        token="";
                    }
                    switch(c)
                    {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':state=2;break;
                        case '.':state=3;break;
                        case 'e':
                        case 'E':state=5;break;
                        default:
                            if(c>='a'&&c<'e'||c>'e'&&c<='z'||c>='A'&&c<'E'||c>'E'&&c<='Z')
                            {
                                state=20;
                                if(forward==ab.size())
                                {
                                token+=c;
                                string er;
                                er+="第"+to_string(line_count+1)+"行"+token+"非法";
                                err.push_back(er);
                                }
                            }
                            forward--;
                            state=0;
                            cout << "<NUM," << token << '>' << endl;  
                            num_count++;
                            token="";
                            break;
                    };
                    break;
                case 3://小数点状态
                    token+=c;
                    c=get_char(ab,c);
                    if(c>='0'&&c<='9')
                    {
                        state=4;
                        if(forward==ab.size())
                        {
                            token+=c;
                            cout << "<NUM," << token << '>' << endl; 
                            num_count++;
                            token="";
                        }
                    }
                    else
                    {
                        state=0;
                    }
                    break;
                case 4://小数状态
                    {
                        token+=c;
                        c=get_char(ab,c);
                        if(forward==ab.size()&&c>='0'&&c<='9')
                        {
                            token+=c;
                            cout << "<NUM," << token << '>' << endl;  
                            num_count++;
                            token="";
                        }
                        switch (c)
                        {
                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9':
                            state=4;
                            break;
                            case 'E':
                            case 'e':state=5;break;
                            default://识别出小数
                                forward--;
                                state=0;
                                cout << "<NUM," << token << '>' << endl;  
                                num_count++;
                                token="";
                                break;
                        };
                        break;
                    }
                case 5://指数状态
                    token+=c;
                    c=get_char(ab,c);
                    switch (c)
                    {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                        state=7;
                        if(forward==ab.size())
                        {
                            token+=c;
                            cout << "<NUM," << token << '>' << endl; 
                            num_count++;
                            token="";
                        }
                        break;
                        case '+':
                        case '-':state=6;break;
                        default:
                            forward--;
                            state=0;
                            string er;
                            er+="第"+to_string(line_count+1)+"行指数"+token+"非法";
                            err.push_back(er);
                            token="";
                            break;
                    };
                    break;
                case 6:
                    token+=c;
                    c=get_char(ab,c);
                    if(c>='0'&&c<='9')
                    {
                        state=7;
                        if(forward==ab.size())
                        {
                            token+=c;
                            cout << "<NUM," << token << '>' << endl; 
                            num_count++;
                            token="";
                        }
                    }
                    else
                    {
                        forward--;
                        state=0;
                        string er;
                        er+="第"+to_string(line_count+1)+"行指数"+token+"非法";
                        err.push_back(er);
                        token="";
                    };
                    break;
                case 7:
                    token+=c;
                    c=get_char(ab,c);
                    if(forward==ab.size()&&c>='0'&&c<='9')
                    {
                        token+=c;
                        cout << "<NUM," << token << '>' << endl; 
                        num_count++;
                        token="";
                    }
                    if(c>='0'&&c<='9')
                    {
                        state=7;
                    }
                    else
                    {
                        forward--;
                        state=0;
                        cout << "<NUM," << token << '>' << endl;  
                        num_count++;
                        token="";
                    };
                    break;
                case 8://<状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是>=号
                            state=0;
                            cout << "<OPERATOR," << "<=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '<' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                    
                case 9://>状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '=':
                            //token+=c;
                            state=0;
                            cout << "<OPERATOR," << ">=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '>' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 10://:状态
                case 11://+状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是+=号
                            state=0;
                            cout << "<OPERATOR," << "+=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        case '+'://判断是否是++号
                            state=0;
                            cout << "<OPERATOR," << "++" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '+' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 12://-状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是-=号
                            state=0;
                            cout << "<OPERATOR," << "-=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        case '-'://判断是否是--号
                            state=0;
                            cout << "<OPERATOR," << "--" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        case '>'://判断是否是->号
                            state=0;
                            cout << "<SEPARATOR," << "->" << '>' << endl;
                            separator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '-' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 13://*状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是*=号
                            state=0;
                            cout << "<OPERATOR," << "*=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '*' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 14:///状态判断是否是除号或注释
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是/=号
                            state=0;
                            cout << "<OPERATOR," << "/=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        case '/'://判断是否是注释
                            state=0;
                            forward=ab.size();
                            token="";
                            break;
                        case '*'://判断是否是注释
                            state=18;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '/' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 15://&状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '&'://判断是否是&&号
                            state=0;
                            cout << "<OPERATOR," << "&&" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '&' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 16://|状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '|'://判断是否是||号
                            state=0;
                            cout << "<OPERATOR," << "||" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '|' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 17://!状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是!=号
                            state=0;
                            cout << "<OPERATOR," << "!=" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '!' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 18:///*注释状态
                    while(1)
                    {
                        //token+=c;
                        c=get_char(ab,c);
                        if(c=='*')
                        {
                            char x=ab.at(forward);
                            if(x=='/')
                            {
                                state=0;
                                c=get_char(ab,c);
                                break;
                            }
                        }
                        
                    }
                    break;
                case 19://=状态
                    token+=c;
                    c=get_char(ab,c);
                    switch(c)
                    {
                        case '='://判断是否是==号
                            state=0;
                            cout << "<OPERATOR," << "==" << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                        default:forward--;
                            state=0;
                            cout << "<OPERATOR," << '=' << '>' << endl;
                            operator_count++;
                            token="";
                            break;
                    };
                    break;
                case 20://错误状态
                    token+=c;
                    c=get_char(ab,c);
                    if(c!=' '&&c!='\t')
                    {
                        state=20;
                        if(forward==ab.size())
                        {
                            token+=c;
                            string er;
                            er+="第"+to_string(line_count+1)+"行"+token+"非法";
                            err.push_back(er);
                        }
                    }
                    else
                    {
                        forward--;
                        state=0;
                        string er;
                        er+="第"+to_string(line_count+1)+"行"+token+"非法";
                        err.push_back(er);
                        token="";
                    }
                    break;
                case 21://转义字符状态
                    token+=c;
                    c=get_char(ab,c);
                    state=0;
                    token+=c;
                    cout << "<SEPARATOR," << token << '>' << endl;
                    separator_count++;
                    token="";
                    char_count--;
                    break;
            };
        }
        while(forward<ab.size());//如果不读到末尾
    }//*/
    void output()//输出函数
    {
        cout << "行数为：" << line_count << endl;
        cout << "关键字个数为：" << keyword_count << endl;
        cout << "分隔符个数为：" << separator_count << endl;
        cout << "运算符个数为：" << operator_count << endl;
        cout << "标识符个数为：" << identifier_count << endl;
        cout << "数字总数为：" << num_count << endl;
        cout << "字符总数为：" << char_count << endl;  
        if(err.size()>0)
        cout << "错误为：" << endl;
        for(int i=0;i<err.size();i++)
        {
            cout << err[i] << endl;
        }
    }
};
int main()
{
    analysis ANALYSIS;
    string temp,filename;
    cout << "请输入进行词法分析的文件名" << endl;
    cin >> filename;
    //filename+=".txt";
    ifstream fin(filename,ios::in);
    while(std::getline(fin,temp))
    {
        string buffer;
        buffer=temp;//读入缓冲区
        if(buffer=="")//空行
        {
            line_count++;
            char_count+=buffer.length()+1;
            temp="";
            continue;
        }
        char a=buffer.at(0);
        if(a=='#')//删去预编译代码，不交给词法分析程序处理
        {
            line_count++;
            char_count+=buffer.length()+1;
            temp="";
            continue;
        }
        ANALYSIS.forward=0;
        ANALYSIS.ana(buffer);
        line_count++;
        char_count+=buffer.length()+1;//添加'\n'符号
        temp="";
    }
    fin.close();
    ANALYSIS.output();
    return 0;
}
