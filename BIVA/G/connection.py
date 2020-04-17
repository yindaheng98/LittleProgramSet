import mysql.connector
connection = mysql.connector.connect(
    host='localhost',
    user='Hospital',
    passwd='Hospital',
    database='Hospital',
    auth_plugin='mysql_native_password'
    )
