GEN=bin/GenProtocol
GENROOT=Generated
PKG="net.protocol"
QUITE=0

chmod +x $GEN

function Generate()
{
    if [ ! -d $PROTDST ]; then
        mkdir -p $PROTDST
    fi
    FS=`ls XML/*.xml`
    for f in $FS
    do
        $GEN $QUITE $f $GENROOT $PKG
    done
}
Generate