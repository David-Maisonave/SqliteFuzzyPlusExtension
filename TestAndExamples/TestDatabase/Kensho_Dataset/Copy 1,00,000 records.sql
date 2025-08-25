DELETE FROM items;
INSERT INTO items (labels, description)
select labels, description from k6.items 
where labels is NOT NULL and description is not NULL
LIMIT 1000000;