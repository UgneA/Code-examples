SET STORAGE_ENGINE = INNODB;
#Script creates database named BlogDB
DROP DATABASE IF EXISTS BlogDB;
CREATE DATABASE BlogDB;
USE BlogDB;

#Creates Editor table
CREATE TABLE Editor(
	ed_Username 	VARCHAR(20) NOT NULL,
	ed_Name	 	VARCHAR(50) NOT NULL,
	ed_Email		VARCHAR(50) NOT NULL,
	ed_DoB		DATE NOT NULL,
	ed_BlogTitle	VARCHAR(50) NOT NULL,
	PRIMARY KEY(ed_Username)	
);

#Inserts sample data
INSERT INTO Editor values('MightyLuke', 'Luke Smith','luke364@hotmail.com',19831121,'Everyday knowledge');
INSERT INTO Editor values('oDaydreamer','Cindy Brown','cici94@gmail.com',19940724,"Cindy's thoughts");

#Creates post table
CREATE TABLE Post(
	po_Title	VARCHAR(50) NOT NULL,
	po_Time		TIMESTAMP NOT NULL,
	po_Text		VARCHAR(1000) NOT NULL,
	po_ID		INT UNSIGNED NOT NULL,
	po_UserN	VARCHAR(20) NOT NULL,
	PRIMARY KEY(po_ID),
	FOREIGN KEY (po_UserN) REFERENCES EDITOR(ed_Username)
);

#Inserts sample data
INSERT INTO Post values
	('Scheduling difficulties','2014-12-01 18:24:53','text',1,'MightyLuke'),
	('Morning laziness','2010-07-24 10:05:37','text1',2,'MightyLuke'),
	('Christmas Hype','2012-12-23 22:57:07','text2',3,'MightyLuke'),
	('Hello Spring!','2014-03-01 10:23:42','text3',4,'MightyLuke'),
	('Facebook trends','2014-08-21 20:39:22','text text',11,'oDaydreamer'),
	('Top 10 Christmas meals','2013-12-15 17:43:52','text text1',22,'oDaydreamer');

CREATE TABLE Comments(
	co_Name	VARCHAR(50),
	co_Email	VARCHAR(50),
	co_Text 	VARCHAR(300) NOT NULL,
	co_Time		TIMESTAMP NOT NULL,
	co_ID		INT UNSIGNED NOT NULL,	
	co_postID	INT UNSIGNED NOT NULL,	
	PRIMARY KEY(co_ID),
	FOREIGN KEY (co_postID) REFERENCES Post(po_ID)
);

#Inserts sample data
INSERT INTO Comments values('Mike',NULL,'Mhm','2013-12-20 19:37:22',1,22),
	(NULL,NULL,'Who cares','2012-12-24 12:23:03',2,3),
	('Samantha','sammy111@mail.com','Same troubles','2014-12-03 12:54:12',3,1),
	(NULL,NULL,':D','2014-09-05 23:12:37',4,11),
	('Laura','secret@hotmail.com','Yay, spring!','2014-03-02 18:43:21',5,4),
	('Lin',NULL,'Eh...','2010-09-01 22:12:13',6,2),
	('Jack',NULL,'Can not wait!','2012-12-24 09:12:59',7,3),
	('Thomas',NULL,'Wait what?','2014-12-13 15:13:01',8,2),
	('Greta','gretut@mail.lv','Just on time ^^!','2014-12-19 20:15:18',9,22),
	('John','JohnSnowy@mail.pl',"They're awesome!",'2014-12-22 12:05:27',10,22);

#Creates Category table
CREATE TABLE Category(
	ca_Title	VARCHAR(20) NOT NULL,
	ca_ID		INT UNSIGNED NOT NULL,
	PRIMARY KEY(ca_ID)
);

#Inserts sample data
INSERT INTO Category values('General',1),
	('Musing',2),
	('Social',3),
	('Work',4);

#Creates table for categories and posts
CREATE TABLE CatePost(
	post_ID	INT UNSIGNED NOT NULL,	
	cate_ID	INT UNSIGNED NOT NULL,
	PRIMARY KEY(post_ID, cate_ID),
	FOREIGN KEY (post_ID) REFERENCES Post(po_ID),
	FOREIGN KEY (cate_ID) REFERENCES Category(ca_ID)
);

#Inserts sample data
INSERT INTO CatePost values(1,1),
	(1,4),
	(22,1),
	(2,2),
	(3,1),
	(3,2),
	(11,2),
	(11,3),
	(4,2);

#Query 1
SELECT ed_Name AS Name, ed_Email AS Email, YEAR(curdate()) - YEAR(ed_DoB) - (RIGHT(curdate(),5) < RIGHT(ed_DoB,5)) 
AS Age 
FROM Editor;

#Query 2
SELECT 
ed_Username AS Username, 
ed_BlogTitle AS BlogTitle,
	(SELECT COUNT(po_Title)FROM Post WHERE ed_Username=po_UserN) 
	AS NumberOfPosts 
FROM Editor;

#Query 3
SELECT 
po_UserN AS Username, 
po_Title AS Title, 
po_Time AS PostTime,
GROUP_CONCAT(ca_Title) AS Category
FROM CatePost,Category,Post
WHERE post_ID=po_ID AND cate_ID=ca_ID
GROUP BY po_Title;
