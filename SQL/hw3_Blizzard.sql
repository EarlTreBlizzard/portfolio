DROP TABLE enrolls;
DROP TABLE teaches;
DROP TABLE student;
DROP TABLE class;
DROP TABLE instructor;


CREATE TABLE student (
student_id varchar(15),
student_name varchar(30) not null,
major varchar(30) not null,
gpa float(4) default 0.0,
PRIMARY KEY(student_id));

CREATE TABLE class (
schedule_num varchar(10),
semester varchar (10),
course_name varchar (50) not null,
course_number varchar (15) not null,
credit varchar (2)not null,
department varchar (10) not null,
meeting_time varchar (15),
meeting_place varchar (20),
class_size_limit integer not null,
PRIMARY KEY (schedule_num,semester));

CREATE TABLE instructor (
name varchar (20),
department varchar (10),
office varchar(5),
title varchar(35),
PRIMARY KEY (name));

CREATE TABLE enrolls (
student_id varchar(15),
schedule_num varchar(10),
semester varchar(10),
grade varchar (2) default 'A',
PRIMARY KEY (student_id,schedule_num,semester),
FOREIGN KEY ( student_id) references student(student_id),
FOREIGN KEY ( schedule_num,semester) references class(schedule_num, semester)
);

CREATE TABLE teaches (
name varchar(20),
schedule_num varchar(10),
semester varchar (10),
PRIMARY KEY (name,schedule_num,semester),
FOREIGN KEY ( name) references instructor ( name),
FOREIGN KEY ( schedule_num, semester) references class(schedule_num, semester)
);

INSERT INTO student(student_id,student_name,major,gpa) VALUES('B001','bob','compsci',4.0);
INSERT INTO student(student_id,student_name,major,gpa) VALUES('B002','sally','compsci',3.0);
INSERT INTO student(student_id,student_name,major,gpa) VALUES('B003','jordon','compsci',3.5);

INSERT INTO class(schedule_num,semester,course_name,course_number,credit,department,class_size_limit)
		VALUES('20','Spring13','Database Design','CSCI3700','3','CSCI',40);
INSERT INTO class(schedule_num,semester,course_name,course_number,credit,department,class_size_limit)
		VALUES('23','Spring13','Game Design','CSCI3750','2','CSCI',20);
INSERT INTO class(schedule_num,semester,course_name,course_number,credit,department,class_size_limit)
		VALUES('30','Spring13','Software Design','CSCI4000','4','CSCI',100);

INSERT INTO instructor(name,department,office,title) VALUES('Keshore','CSCI','1440','director of class size');
INSERT INTO instructor(name,department,office,title) VALUES('Ding','CSCI','2020','director of class location');
INSERT INTO instructor(name,department,office,title) VALUES('Abrahamson','CSCI','5780','director of class study');

INSERT INTO enrolls(student_id,student_name,semester,grade) VALUES('B001','bob','Spring13','B');
INSERT INTO enrolls(student_id,student_name,semester,grade) VALUES('B001','bob','Spring12','F');
INSERT INTO enrolls(student_id,student_name,semester,grade) VALUES('B002','sally','Spring13','A');
INSERT INTO enrolls(student_id,student_name,semester,grade) VALUES('B002','sally','Spring15','A');
INSERT INTO enrolls(student_id,student_name,semester,grade) VALUES('B003','jordon','Spring13','B');

INSERT INTO teaches(name,schedule_num,semester) VALUES('Keshore','23','Spring13');
INSERT INTO teaches(name,schedule_num,semester) VALUES('Keshore','30','Spring13');
INSERT INTO teaches(name,schedule_num,semester) VALUES('Ding','20','Spring13');
INSERT INTO teaches(name,schedule_num,semester) VALUES('Abrahamson','20','Spring13');
INSERT INTO teaches(name,schedule_num,semester) VALUES('Abrahamson','30','Spring13');

COMMIT;

SELECT course_name, course_number, semester
FROM class
WHERE course_name like '%Database%';

SELECT student_name, major
FROM student
INNER JOIN enrolls
ON
student.student_id=enrolls.student_id
INNER JOIN class
ON
student.schedule_num=class.schedule_num
WHERE semester = 'Spring13' and course_number = 'CSCI3700'
ORDER BY major DESC, student_name DESC;

SELECT major
COUNT(student_id)
FROM student
WHERE gpa > 3.5
GROUP BY major;
