SELECT e.employee_id,e.first_name,e.last_name,e.email,e.phone_number,j.job_title,d.department_name
FROM employees e LEFT JOIN jobs j ON j.job_id = e.job_id 
LEFT JOIN departments d ON d.department_id = e.department_id
WHERE e.first_name LIKE '%';

SELECT * FROM countries;
SELECT * FROM departments;
SELECT * FROM dependents;
SELECT * FROM employees;
SELECT * FROM jobs;
SELECT * FROM locations;
SELECT * FROM regions;
SELECT * FROM user_info;

