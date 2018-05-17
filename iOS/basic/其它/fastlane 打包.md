fastlane 自动化安装

1.安装xcode 工具	

​	xcode-select install，如果没有安装，会弹出对话框，点击安装，如果提示xcode-select error 表示已经安装

2.安装fastlane

​	通过gem 安装

​	sudo gem install fastlane -NV

​	安装完成之后，可以执行fastlane —version查看当前版本号

3.初始化fastlane

​	cd 到工程目录，执行 fastlane init

​	init 之后会选择安装模式，四种安装模式

 	1. automate screenshots
 	2. automate beta distribution to TestFlight、自动配置testflight
 	3. automate app store distribution 自动发布到appstore
 	4. manual setup、手动配置内容

4.选择不同设置有不同的操作步骤，手动配置内容

5.配置文件讲解

​	Appflie：存储开发者相关信息

​			app_identifier(bundle identifier)、app_id（email address）、team_id （团队id，在develop网站点击个人信息可以查看）

​	Fastfile：核心文件，用于命令行调用和处理具体的流程，lane相当于一个方法或者函数

​	Deliverfile：deliver工具的配置文件

​	metadata：元数据文件夹

​	Matchfile：Match操作对应的配置文件

​	screenshots：截图文件夹



 6.常用命令

​	fastlane actions：展示所有有效action列表

​	fastlane action [action_name]:展示一个action的详细说明，使用方法等

​	fastlane lanes：展示fastfile中的所有lane

​	fastlane list：展示fastfile中所有的有效lane

、	fastlane new_action：创建一个新的action

​	fastlane env：打印fastlane、ruby环境

7.fastlane声明周期

​	

| 执行顺序 | 方法名      | 说明                                         |
| -------- | ----------- | -------------------------------------------- |
| 1        | before_all  | 在执行lane之前只执行一次                     |
| 2        | before_each | 每次执行lane之前都会执行一次                 |
| 3        | lane        | 自定义的任务                                 |
| 4        | after_each  | 每次执行lanee之后都会执行一次                |
| 5        | after_all   | 在执行lane成功结束之后执行一次               |
| 6        | error       | 在执行上述情况任意环境报错都会终止并执行一次 |



一个完整fastfile 

​	This file contains the fastlane.tools configuration

​	default_platform(:ios)

​	platform :ios do
  	desc "Description of what the lane does"
 	 lane :custom_lane do
    # add actions here: https://docs.fastlane.tools/actions
 	 end

​	  desc "firim 测试分发"
 	 lane :firmTest do
     build_app(workspace:"xxxx.xcworkspace",scheme:"xxxx",export_method:"ad-hoc",output_directory:"./fastlane/package",configuration:"Release")
     firim(firim_api_token:"xxxxxxxxxxxx")
​	  end


​	  desc "pgyer 测试分发"
​	lane :pgyerTest do
  			   build_app(workspace:"xxxx.xcworkspace",scheme:"xxxxx",export_method:"ad-hoc",output_directory:"./fastlane/package",configuration:"Release")
      pgyer(api_key:"xxxxxx",user_key:"xxxxxxxxxxx")
  end

