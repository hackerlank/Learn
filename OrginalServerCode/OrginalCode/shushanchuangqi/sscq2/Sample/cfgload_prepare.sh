
#!/bin/bash

source prepare.sh

# 更新所有配置加载程序
cd $CFGLOAD && svn up && cd -
if [ $? -ne 0 ]; then
    echo  "ERROR: svn up ConfigLoad."
    return
fi

# 更新所有配置数据文件
cd $CFGTABL && svn up && cd -
if [ $? -ne 0 ]; then
    echo  "ERROR: svn up Config Table."
    return
fi

# 复制所有配置加载程序
copy_cfgcode
# 复制所有配置数据
copy_cfgtable

