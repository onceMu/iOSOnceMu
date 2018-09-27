RN debug模式加载缓存解决方案

一

​	rm -rf node_modules/

​	rm -rf iOS/build



二

​	rm -rf ~/.rncache

​	watchman watch-del-all

​	npm start -- reset-cache
​    
​    查看8081端口
​    sudo lsof -i :8081
​    sudo kill -9 61342（即pid
​    
​    
​    
​    code-push release-react <appName> <platform> -t 版本  -d 环境  --des 描述 -m true （强制更新）
​    
​    
​    code-push release-react <appName> <platform> -t 版本  -d 环境  --des 描述 -m true （强制更新）
​    
​    
​    // 清除历史部署记录
​    code-push deployment clear <appName> Production or Staging
​    
​    
​    // 回滚

