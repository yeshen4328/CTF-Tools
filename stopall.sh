kill -9 `ps -ef|grep test|grep -v grep|awk '{print $2}' ` 
