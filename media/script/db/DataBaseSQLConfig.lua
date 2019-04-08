local P = {}
------------------------------------------------------------------------
-- @brief 数据库语句
P.dbCreateWorld = "create database world_%d;"
P.dbUseWorld = "use world_%d;"
P.tbRoleCreate = "create table tb_role(id int(4) not null primary key auto_increment, role_name varchar(32) not null, role_id double not null, role_values blob default null, role_objects blob default null, role_mails blob default null);"
P.tbLogCreate = "create table tb_log(id int(4) not null primary key auto_increment, role_name varchar(32) not null, role_id double not null, time double not null, type_name varchar(64) not null, data blob default null);"
P.tbLogInsert = "insert into tb_log(role_name, role_id, time, type_name, data) values('%s', '%s', '%s', '%s', ?);"
P.tbRoleInsert = "insert into tb_role(role_name, role_id) values('%s', %d);"
P.tbRoleUpdateValues = "update tb_role set role_values=? where role_id=%d;"
P.tbRoleUpdateObjets = "update tb_role set role_objects=? where role_id=%d;"
P.tbRoleSelectValues = "select role_name, role_values from tb_role where role_id= %d;"
P.tbRoleSelectObjects = "select role_objects from tb_role where role_id=%d;"
P.tbRoleSelectAllNames = "select role_name from tb_role;"
P.tbRoleDeleteRole = "delete from tb_role where role_id=%d;"
P.tbRoleSelectMails = "select role_mails from tb_role where role_id=%d;"
P.tbRoleUpdateMails = "update tb_role set role_mails=? where role_id=%d;"
P.tbGlobalDatasCreate = "create table tb_global_datas(id int(4) not null primary key auto_increment, key_name varchar(32) not null, table_length double not null, table_data blob default null);"
P.tbGlobalDatasSelectKeyName = "select key_name from tb_global_datas"
P.tbGlobalDatasSelectData = "select table_length, table_data from tb_global_datas where key_name='%s';"
P.tbGlobalDatasUpdate = "update tb_global_datas set table_length=%d, table_data=? where key_name='%s';"
P.tbGlobalDatasInsert = "insert into tb_global_datas(table_length, key_name) values(%d, '%s');"
P.tbLoginCreate = "create table tb_login (id int(4) not null primary key auto_increment, user varchar(32) not null, password varchar(32), role_name varchar(32) not null, role_id double not null);"
P.tbLoginInsert = "insert into tb_login(user, password, role_name, role_id) values('%s', '%s', '%s', %d);"
P.tbLoginSelect = "select role_id from tb_login where user='%s' and password='%s';"
P.tbLoginSelectAll = "select user from tb_login;"
------------------------------------------------------------------------
return P