1,所有脚本放在Sample/Generated/Scripts
2,任务编辑器生成的文件放在Sample/Generated/Config/Conf/Task
3,地图编辑器生成的文件放在Sample/Generated/Config/Conf/Map
4,数据库脚本放在Sample/Generated/Config/DB
5,协议生成后的代码放在Sample/Generated/ProtoGen
6,Tools/GenConfig03 这个工具支持所有是2003的配置文件，这生成配置后会生成Generated/client,Generated/server两个目录
    Generated/server/code里的代码是要被复制到Sample/Generated/ConfigLoad里，用来加载配置用
    Generated/server/table里的xml文件是要被复制到Sample/Generated/Config/Conf/Table里，这些xml文件是配置的具体数值
//7,如果配置发生变化，使用"svn://192.168.88.250/sscq2/策划/配置/配置文件/ExecTool.exe"生成后提交到svn，并在Sample里执行prepare.sh
7,如果配置发生变化，找策划帮忙改表吧，现在没权限改了。

配置相关的东西请查看svn://192.168.88.250/sscq2/策划/配置/配置文件/Readme.txt


