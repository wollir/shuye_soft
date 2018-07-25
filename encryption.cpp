#include "encryption.h"

//单个字符异或运算
inline char MakecodeChar(char &c,int key){
    return c=c^key;
}
//单个字符解密
inline char CutcodeChar(char &c,int key){
    return c^key;
}
//加密
void encryption::Makecode(std::string &pstr){
    int len=pstr.size();//获取长度
    for(int i=0;i<len;i++)
        pstr[i]=MakecodeChar(pstr[i],key[i%key.size()]);
}
//解密
void encryption::Cutecode(std::string &pstr){
    int len=pstr.size();
    for(int i=0;i<len;i++)
       pstr[i] = CutcodeChar(pstr[i],key[i%key.size()]);
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//    int key[]={1,2,3,4,5};//加密字符
//    char s[]="www.xiaozhuanggushi.com";
//    char *p=s;
//    cout<<"加密前:"<<p<<endl;
//    Makecode(s,key);//加密
//    cout<<"加密后:"<<p<<endl;
//    Cutecode(s,key);//解密
//    cout<<"解密后:"<<p<<endl;


//    int c;
//    cin>>c;
//    return 0;
//}

encryption::encryption(QVector<int> key1)
{
    key = key1;
}
