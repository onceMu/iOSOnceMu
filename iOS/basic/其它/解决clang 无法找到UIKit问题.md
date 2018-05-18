解决clang rewriteoc 缺少 UIKit/UIKit.h 问题



1.进入终端，输入 vim ~/.bash_profile

2.进入编辑状态输入  alias rewriteoc='clang -x objective-c -rewrite-objc -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk‘

3.保存退出vim

4.重启 source ~/.bash_profile