1.在项目根目录下面创建文件夹，ReactNative（文件夹名字可以随意，但是后续所有文件根目录都是当前文件夹）



2.在ReactNative 文件目录下面，生成package.json 文件，我是直接从原有rn项目拷贝



3.在ReactNative 文件夹 执行nom install 命令，生成node_modules文件



4.修改package.json 文件中的 postinstall命令行，"postinstall": "sed -i '' 's/#import <RCTAnimation\\/RCTValueAnimatedNode.h>/#import <React\\/RCTValueAnimatedNode.h>/' ./node_modules/react-native/Libraries/NativeAnimation/RCTNativeAnimatedNodesManager.h; sed -i '' 's/#import <fishhook\\/fishhook.h>/#import <React\\/fishhook.h>/' ./node_modules/react-native/Libraries/WebSocket/RCTReconnectingWebSocket.m" 这个命令行主要是解决FaceBook内部头文件引用错误fishbook以及RCTValueAnimatedNode



5.执行npm install postinstall命令，修改本地的文件加载问题



6.在原有的iOS 工程podfile 文件中，引入React所需要的库



 pod 'React', :path => './ReactNative/node_modules/react-native', :subspecs => [



​       'Core',



​       'ART',



​       'RCTActionSheet',



​       'RCTImage',



​       'RCTNetwork',



​       'RCTPushNotification',



​       'RCTSettings',



​       'RCTText',



​       'RCTVibration',



​       'RCTWebSocket',



​       'RCTLinkingIOS',



​       'RCTAnimation',



​       'CxxBridge',



​       'DevSupport',



   ]



   \# Explicitly include Yoga if you are using RN >= 0.42.0



pod 'yoga', :path => './ReactNative/node_modules/react-native/ReactCommon/yoga'



   pod 'glog', :podspec => './ReactNative/node_modules/react-native/third-party-podspecs/glog.podspec'



   pod 'Folly', :podspec => './ReactNative/node_modules/react-native/third-party-podspecs/Folly.podspec'



其中yoga、glog、folly 是必须的第三方依赖，由于存在yoga内部的podspec头文件引入有误，需要找到yoga.podspec 文件并进行修改，在yoga.podspec末尾加上spec.public_header_files = 'yoga/Yoga.h', 'yoga/YGEnums.h', 'yoga/YGMacros.h' 命令



7.执行 pod install 命令，管理react 需要的库

上述所有操作是在RN0.55.4版本下进行操作

8.在运行过程中可能会多次出现 native module can not null 错误，可以在xcode 的console 中找到相关错误提示，然后将需要的模块加载到iOS build phases 的link binart with libraries 或者使用pod 直接管理

9.glog  config.h 文件找不到

cd node_mudules/react-native/third-party/glog-0.34

执行 ../../scripts/[ios-configure-gloh.sh](/Users/le/Library/Application Support/typora-user-images/E9A5FEEB-C304-49C4-979E-870FADD3886F/ios-configure-gloh.sh)



10..在ReactNative的/node_modules/react-native/ReactCommon/yoga 文件夹中找到“yoga.podspec”文件并打开，将

spec.public_header_files ='yoga/Yoga.h','yoga/YGEnums.h','yoga/YGMacros.h'

解决yoga文件目录的问题



11.pod 中加入use_frameworks! 

12. 新的错误
在React 的pod framework 中 需要加入 DoubleConversion.framework 和 glog.framework 依赖



