# In the below line, set the path to the correct folder where you have extracted
# the Java tar.gz file
export JAVA_HOME=/home/anarayan/bin/amazon-corretto-11.0.8.10.1-linux-x64
export PATH=$JAVA_HOME/bin:$PATH
echo "JAVA_HOME set to: " $JAVA_HOME
java -version
echo "Java 11 activated"