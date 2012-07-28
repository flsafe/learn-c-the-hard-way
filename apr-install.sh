#!/bin/bash

set -e

cd /tmp

curl -L -O 'http://archive.apache.org/dist/apr/apr-1.4.6.tar.gz'
tar -xvzf 'apr-1.4.6.tar.gz'

cd 'apr-1.4.6'

./configure
make
make install

cd /tmp
rm -rf 'apr-1.4.6'
rm -f 'apr-1.4.6.tar.gz'


curl -L -O 'http://archive.apache.org/dist/apr/apr-util-1.4.1.tar.gz'
tar -xvzf 'apr-util-1.4.1.tar.gz'

cd 'apr-util-1.4.1'

./configure --with-apr=/usr/local/apr
make
make install

cd /tmp
rm -rf 'apr-util-1.4.1'
rm -f 'apr-util-1.4.1.tar.gz'
