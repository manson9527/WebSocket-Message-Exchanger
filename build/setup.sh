#!/bin/sh

LIBS="../libs"
BOOST="boost_1_61_0"
WEBSOCKETPP="websocketpp"
RAPIDJSON="rapidjson"

# check libs
if [ ! -d "$LIBS" ]; then 
    mkdir "$LIBS"
else
    echo "check $LIBS ----- yes"
fi

cd $LIBS
echo "change working directory to `pwd`"

# check boost
if [ ! -d "$BOOST" ]; then 
    echo "check $BOOST ----- no"
    if [ ! -f "boost_1_61_0.tar.bz2" ]; then
        wget http://jaist.dl.sourceforge.net/project/boost/boost/1.61.0/boost_1_61_0.tar.bz2
    fi
    tar zxvf boost_1_61_0.tar.bz2
    mv boost_1_61_0 boost
else
    echo "check $BOOST ----- yes"
fi

# check websocketpp
if [ ! -d "$WEBSOCKETPP" ]; then 
    echo "check $WEBSOCKETPP ----- no"
else
    echo "check $WEBSOCKETPP ----- yes"
fi

# check rapidjson
if [ ! -d "$RAPIDJSON" ]; then 
    echo "check $RAPIDJSON ----- no"
else
    echo "check $RAPIDJSON ----- yes"
fi
