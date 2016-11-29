GEN=bin/GenProtocol
GENROOT=Generated
PKG="net.protocol"
QUITE=0

chmod +x $GEN

function Generate()
{
    if [ ! -d $GENROOT ]; then
        mkdir -p $GENROOT
    fi

    FS=`ls XML/*.xml`
    for f in $FS
    do
        $GEN $QUITE $f $GENROOT $PKG
    done
}

function Sync()
{
    if [ ! -d $PROTDST ]; then
        mkdir -p $PROTDST
    fi
    rsync -rvc --exclude '.svn' "$GENROOT/CPlusPlus/" $PROTDST/ --delete

    if [ ! -d $ROBOTDST ]; then
        mkdir -p $ROBOTDST
    fi
    echo "Path$ROBOTDST"
    rsync -rvc --exclude '.svn' "$GENROOT/Ruby/" $ROBOTDST/ --delete
}

if [ "$PROTDST" == "" -o "$ROBOTDST" == "" ]; then
    #echo "请提供dst.local设置好PROTDST。PROTDST是生成协议后文件所要拷贝去的目录。如: ~/sscq2/Sample/Generated/ProtoGen"
    source ./dst.local
fi
Generate
Sync

