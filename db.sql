SELECT * FROM user_info;

SELECT * FROM employee;

CREATE TABLE employee (
	employee_id SERIAL PRIMARY KEY,
	first_name VARCHAR(50) NOT NULL,
	last_name VARCHAR(50) NOT NULL,
	phone VARCHAR(12),
	email VARCHAR(50),
	address VARCHAR(50),
	salary INT NOT NULL,
	birthdate DATE NOT NULL,
	sex BOOL,
	department_id INT,
	supervisor_id INT
);

