SELECT invoice_id, invoice_total, 'low' AS label
FROM ap.invoices
WHERE invoice_total < 1000

UNION

SELECT invoice_id, invoice_total, 'medium' AS label
FROM ap.invoices
WHERE invoice_total BETWEEN 1000 AND 3000

UNION

SELECT invoice_id, invoice_total, 'high' AS label
FROM ap.invoices
WHERE invoice_total > 3000

ORDER BY invoice_id



