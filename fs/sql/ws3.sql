/* 1 Find the model number, speed and hd capacity for all the PCs with prices below 500. Result set : model, speed, hd*/
SELECT 
    model, speed, hd
FROM
    PC
WHERE
    price < 500;

/* 2 List all printer makers. result set : makers */
SELECT DISTINCT
    maker
FROM
    Product
WHERE
    type = 'Printer';

/* 3  Find the model number , RAM, screen size of the Laptops with prices over $1000 */
SELECT 
    model, ram, screen
FROM
    Laptop
WHERE
    price > 1000;

/* 4 List all the color printers models */
SELECT 
    model
FROM
    Printer
WHERE
    color = 'y';

/* 5 Find the model numbers, speed, and hd capacity of the PCs that have 12x CD and prices less than $ 600 or having 24x CD and prices less than $600 */
SELECT 
    model, speed, hd
FROM
    PC
WHERE
    (cd = '12x' OR cd = '24x')
        AND price < 600;

/* 6 Point out the maker and speed of the laptops having hard drive capacity more or equal to 10 GB */
SELECT 
    maker, speed
FROM
    Product
        OUTER JOIN
    (SELECT 
        speed, model
    FROM
        Laptop
    WHERE
        hd >= 10) AS a USING (model);
/* 6 Another form */
        SELECT 
    maker, speed
FROM
    Product
        JOIN
    (SELECT 
        speed, model
    FROM
        Laptop
    WHERE
        hd >= 10) AS a ON Product.model = a.model
        
/* 7 Find out the models and prices for all the products (of any type) produced by maker B */


SELECT 
    model, price
FROM
    Product
        JOIN
    (SELECT 
        model, price
    FROM
        PC UNION SELECT 
        model, price
    FROM
        Laptop UNION SELECT 
        model, price
    FROM
        Printer) AS a USING (model)
WHERE
    maker = 'B';

/* 8 Find out the makers that sell PCs but not laptops */

SELECT DISTINCT
    maker
FROM
    (SELECT 
        maker
    FROM
        Product
    WHERE
        maker IN (SELECT 
                maker
            FROM
                Product
            WHERE
                type = 'PC')) AS a
WHERE
    maker NOT IN (SELECT 
            maker
        FROM
            Product
        WHERE
            type = 'Laptop');
            
/* 9 Find the makers of the PCs that have speed not less than 450 MHz. Result set : maker */

SELECT DISTINCT
    maker
FROM
    Product
        JOIN
    (SELECT 
        model
    FROM
        PC
    WHERE
        speed >= 450) AS a USING (model);

/* 10 Find the models of printers having the highest price, Result set : model, price 
WRONG UNDERSTANDING!!!!!!!*/

SELECT 
    model
FROM
    Printer
ORDER BY price DESC;

/* 11 Find the average speed of PCs */

SELECT 
    AVG(speed)
FROM
    PC;
    
/* 12 Find out the average speed of laptops priced over $1000 */

SELECT 
    AVG(speed)
FROM
    Laptop
WHERE
    price > 1000;

/* 13 Find out the average speed of PCs produced by maker A */

SELECT 
    AVG(speed)
FROM
    PC
        JOIN
    (SELECT 
        model
    FROM
        Product
    WHERE
        maker = 'A') AS a ON PC.model = a.model;
        
/* 13 another form */

SELECT 
    AVG(speed)
FROM
    PC
WHERE
    model IN (SELECT 
            model
        FROM
            Product
        WHERE
            maker = 'A');
            
/* 14 Find out makers who make two or more versions of a model of PC */

SELECT distinct
    maker
FROM
    Product
WHERE
    model IN (SELECT 
            model
        FROM
            PC
        GROUP BY model
        HAVING COUNT(model) > 1);

/* 15 find the hd sizes that are equal among two or more PCs */

SELECT 
    hd
FROM
    PC
GROUP BY hd
HAVING COUNT(hd) >= 2;

/* 16
Find the pairs of PC models having identical speed and Ram. Each resulting pair is shown only once, i.e show (i, j), don't shoe (j. i). 
Result set : model with higher number, model, with lower number. speed, RAM
 */
 
SELECT 
    a.model, b.model, a.speed, a.ram
FROM
    PC a
        JOIN
    (SELECT 
        model, speed, ram
    FROM
        PC) AS b ON a.speed = b.speed AND a.ram = b.ram
        AND a.model > b.model;
        
/* 17
Find the laptop models such that their speed is lower than the slowest PC
*/

SELECT DISTINCT
    model
FROM
    Laptop
WHERE
    speed < (SELECT 
            MIN(speed)
        FROM
            PC);

/* 18 
Find the makers of the cheapest color printers. Result set: maker, price
*/

/*Wrong understanding of thew questions*/
SELECT DISTINCT
    maker, price
FROM
    Product
        JOIN
    (SELECT 
        model, price
    FROM
        Printer
    WHERE
        color = 'y') AS a USING (model)
ORDER BY price ASC;

/* 
Right understanding
*/
SELECT 
    maker, price
FROM
    Product
        JOIN
    (SELECT 
        model, price
    FROM
        Printer
    WHERE
        color = 'y' and price = (select min(price) from Printer where color = "y")) AS a USING (model);

/* 19
For each maker having models in Laptop table, find out the average screen size of the laptops produced by it.
Result set : maker, average screen size
*/

SELECT 
    maker, AVG(screen) AS avg_screen
FROM
    Product
        JOIN
    (SELECT 
        model, screen
    FROM
        Laptop) AS temp_model_screen USING (model)
GROUP BY (maker);

/* 20
Find the makers producing at least three distinct models of PCs
*/

SELECT 
    maker, COUNT(model) temp_model_count
FROM
    Product
WHERE
    type = 'PC'
GROUP BY (maker)
HAVING temp_model_count >= 3;

/* 21
List the highest priced PCs for each maker
*/

SELECT 
    maker, MAX(price)
FROM
    Product
        JOIN
    PC USING (model)
GROUP BY maker;

/* 22
For each value of PC speed that exceeds 600 MHz, find the average price of the PCs with the identical speed */

SELECT 
    speed, AVG(price) avg_price
FROM
    PC
WHERE
    speed > 600
GROUP BY speed;

/* 23
Find the makers producing both a pc having speed not less than 750 MHz and a laptop having speed not less than 750 MHz. Result set : maker 
*/

/*
select distinct maker from
(select maker, speed from Product join PC 
INTERSECT
select maker, speed from Product join Laptop ) as pc_laptop_product
where
speed >= 750;
*/

SELECT 
    maker
FROM
    Product
WHERE
    model IN (SELECT 
            model
        FROM
            PC
        WHERE
            speed >= 750)
        AND maker IN (SELECT 
            maker
        FROM
            Product
        WHERE
            model IN (SELECT 
                    model
                FROM
                    Laptop
                WHERE
                    speed >= 750));