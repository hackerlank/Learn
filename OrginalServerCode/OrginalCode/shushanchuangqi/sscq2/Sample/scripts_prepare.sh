
#!/bin/bash

source prepare.sh

# 更新所有地图配置文件
cd $SCRIPTS && svn up && cd -
if [ $? -ne 0 ]; then
    echo  "ERROR: svn up Config Table."
    return
fi
copy_scripts
