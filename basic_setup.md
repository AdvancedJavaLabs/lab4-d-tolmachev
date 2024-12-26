1. Install the prerequisites:
```
$ sudo apt update
$ sudo apt install -y openjdk-11-jdk openssh-server libssl-dev libtirpc-dev libntirpc-dev
```
2. Download and extract Hadoop:
```
$ wget https://dlcdn.apache.org/hadoop/common/stable/hadoop-3.4.1.tar.gz
$ tar xvzf hadoop-3.4.1.tar.gz
$ rm hadoop-3.4.1.tar.gz
$ export HADOOP_PREFIX <path-to-extracted-hadoop>
```
3. Edit the following configs:
`$HADOOP_PREFIX/etc/Hadoop/hadoop-env.sh`
```
export JAVA_HOME="/usr/lib/jvm/java-11-openjdk-amd64"
```
`$HADOOP_PREFIX/etc/Hadoop/core-site.xml`
```
<configuration>
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://localhost:9000</value>
    </property>
</configuration>
```
`$HADOOP_PREFIX/etc/Hadoop/hdfs-site.xml`
```
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
</configuration>
```
`$HADOOP_PREFIX/etc/Hadoop/mapred-site.xml`
```
<configuration>
    <property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
    </property>
    <property>
        <name>mapreduce.application.classpath</name>
        <value>$HADOOP_MAPRED_HOME/share/hadoop/mapreduce/*:$HADOOP_MAPRED_HOME/share/hadoop/mapreduce/lib/*</value>
    </property>
</configuration>
```
`$HADOOP_PREFIX/etc/Hadoop/yarn-site.xml`
```
<configuration>
    <property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
    </property>
    <property>
        <name>yarn.nodemanager.env-whitelist</name>
        <value>JAVA_HOME,HADOOP_COMMON_HOME,HADOOP_HDFS_HOME,HADOOP_CONF_DIR,CLASSPATH_PREPEND_DISTCACHE,HADOOP_YARN_HOME,HADOOP_HOME,PATH,LANG,TZ,HADOOP_MAPRED_HOME</value>
    </property>
    <property>
        <name>yarn.resourcemanager.hostname</name>
        <value>127.0.0.1</value>
    </property>
</configuration>
```
4. Setup passphraseless ssh:
```
$ ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
$ cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
$ chmod 0600 ~/.ssh/authorized_keys
```
5. Prepare Hadoop filesystem and directories:
```
$ $HADOOP_PREFIX/bin/hdfs namenode -format
$ $HADOOP_PREFIX/sbin/start-dfs.sh
$ $HADOOP_PREFIX/bin/hdfs dfs -mkdir -p /user/<username>
$ $HADOOP_PREFIX/bin/hdfs dfs -mkdir -p /user/<username>/input
$ $HADOOP_PREFIX/bin/hdfs dfs -mkdir -p /user/<username>/programm
$ $HADOOP_PREFIX/bin/hdfs dfs -mkdir -p /user/<username>/tmp
```
6. Compile CPP executable:
```
$ mkdir build
$ cd build
$ cmake .. -DHADOOP_INSTALL_DIR=$HADOOP_PREFIX
$ cmake --build .
```
7. To copy input files into HDFS use:
```
$ $HADOOP_PREFIX/bin/hdfs dfs -put <source> <dest>
```
8. To start Hadoop job use:
```
$ $HADOOP_PREFIX/sbin/start-dfs.sh
$ $HADOOP_PREFIX/sbin/start-yarn.sh
$ $HADOOP_PREFIX/bin/mapred pipes -D mapreduce.pipes.isjavarecordreader=true -D mapreduce.pipes.isjavarecordwriter=true -D mapreduce.output.textoutputformat.separator=, -input <input-dir> -output tmp -program <executable_1> && $HADOOP_PREFIX/bin/mapred pipes -D mapreduce.pipes.isjavarecordreader=true -D mapreduce.pipes.isjavarecordwriter=true -D mapred.output.key.comparator.class=org.apache.hadoop.mapred.lib.KeyFieldBasedComparator -D  mapred.text.key.comparator.options=-rn -D mapreduce.output.textoutputformat.separator=, -input tmp -output <output-dir> -program <executable_2> && $HADOOP_PREFIX/bin/hdfs dfs -rm -r /user/<username>/tmp/*
```
9. To copy output files from HDFS use:
```
$ $HADOOP_PREFIX/bin/hdfs dfs -get <output-dir>/part-00000 <dest>
```
10. To stop Hadoop services use:
```
$ $HADOOP_PREFIX/sbin/stop-yarn.sh
$ $HADOOP_PREFIX/sbin/stop-dfs.sh
```
