USE sakila;

SELECT 
    cst.customer_id,
    cst.first_name,
    cst.last_name,
    count(pym.payment_id) AS rent_count,
    sum(pym.amount) AS total_spent
FROM 
    customer as cst
JOIN 
    payment as pym ON cst.customer_id = pym.customer_id
GROUP BY 
    cst.customer_id
ORDER BY 
    cst.customer_id;
    
