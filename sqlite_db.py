import subprocess as sp
import mysql.connector
from mysql import connector
from mysql.connector import Error

def create_server_connection(host_name, user_name, user_password):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password
        )
        print("MySQL Database connection successful")
    except Error as err:
        print(f"Error: '{err}'")

    return connection

pw = "abcde" # MySQL Terminal password 
db = "Logistics" # This is the name of the database 

connection = create_server_connection("localhost", "root", pw)


def create_database(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        print("Database created successfully")
    except Error as err:
        print(f"Error: '{err}'")

create_database_query = "CREATE DATABASE Logistics"
create_database(connection, create_database_query)

def create_db_connection(host_name, user_name, user_password, db_name):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password,
            database=db_name
        )
        print("MySQL Database connection successful")
    except Error as err:
        print(f"Error: '{err}'")

    return connection

def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
        print("Query successful")
    except Error as err:
        print(f"Error: '{err}'")

create_product_table = """
CREATE TABLE `Product` (
  `ItemId` int,
  `Name` varchar(255),
  `ProductId` int,
  `Tax` int,
  `Price_Without_Tax` int,
  `Company` varchar(255),
  PRIMARY KEY (`ItemId`, `ProductId`)
);
 """

create_administration_table = """
CREATE TABLE `Administration` (
  `Name` varchar(255),
  `Department` varchar(255),
  `Username` varchar(255) PRIMARY KEY,
  `password` varchar(255)
);
 """

create_seller_table = """
CREATE TABLE `Seller` (
  `Seller_Id` int PRIMARY KEY,
  `Seller_Name` varchar(255)
);
 """

create_deliverypartner_table = """
CREATE TABLE `DeliveryPartner` (
  `Status` varchar(255),
  `Company_Name` varchar(255),
  `Name` varchar(255),
  `Unique_Id` int PRIMARY KEY
);
 """

create_customer_table = """
CREATE TABLE `Customer` (
  `Name` varchar(255),
  `Account_Id` int PRIMARY KEY,
  `Address_Country` varchar(255),
  `Address_State` varchar(255),
  `Address_Pincode` int
);
 """

create_paymentcredentials_table = """
CREATE TABLE `Payment_Credentials` (
  `Customer_Account_Id` int PRIMARY KEY,
  `Payment_Credentials` int
);
 """

create_manages_table = """
CREATE TABLE `Manages` (
  `Administration_Username` varchar(255),
  `Customer_AccountID` int,
  `Seller_SellerID` int,
  `Product_ProductID` int,
  `Product_ItemID` int,
  PRIMARY KEY (`Administration_Username`, `Customer_AccountID`, `Seller_SellerID`, `Product_ProductID`, `Product_ItemID`)
);
 """

create_delivery_table = """
CREATE TABLE `Delivery` (
  `Product_ProductID` int,
  `Product_ItemID` int,
  `DeliveryPartner_UniqueID` int,
  PRIMARY KEY (`Product_ProductID`, `Product_ItemID`, `DeliveryPartner_UniqueID`)
);
 """

create_deliveredto_table = """
CREATE TABLE `DeliveredTO` (
  `DeliveryPartner_UniqueID` int,
  `Customer_AccountID` int,
  PRIMARY KEY (`DeliveryPartner_UniqueID`, `Customer_AccountID`)
);
 """

create_soldby_table = """
CREATE TABLE `SoldBy` (
  `Seller_SellerID` int,
  `Product_ItemID` int,
  `Product_ProductID` int,
  PRIMARY KEY (`Seller_SellerID`, `Product_ItemID`, `Product_ProductID`)
);
 """

create_offer_table = """
CREATE TABLE `Offer` (
  `Product_ProductID` int,
  `Product_ItemID` int,
  `Discount` int,
  PRIMARY KEY (`Product_ProductID`, `Product_ItemID`)
);
 """

create_brand_table = """
CREATE TABLE `Brand` (
  `Product_ProductID` int,
  `Product_ItemID` int,
  `Brand_Name` varchar(255),
  PRIMARY KEY (`Product_ProductID`, `Product_ItemID`)
);
 """

connection = create_db_connection("localhost", "root", pw, db)
execute_query(connection, create_product_table)
execute_query(connection, create_administration_table)
execute_query(connection, create_seller_table)
execute_query(connection, create_deliverypartner_table)
execute_query(connection, create_customer_table)
execute_query(connection, create_paymentcredentials_table)
execute_query(connection, create_manages_table)
execute_query(connection, create_delivery_table)
execute_query(connection, create_deliveredto_table)
execute_query(connection, create_soldby_table)
execute_query(connection, create_offer_table)
execute_query(connection, create_brand_table)

alter_brand1 = """
ALTER TABLE `Brand` ADD FOREIGN KEY (`Product_ItemID`) REFERENCES `Product` (`ItemId`);
"""

alter_offer1 = """
ALTER TABLE `Offer` ADD FOREIGN KEY (`Product_ItemID`) REFERENCES `Product` (`ItemId`);
"""

alter_soldby1 = """
ALTER TABLE `SoldBy` ADD FOREIGN KEY (`Seller_SellerID`) REFERENCES `Seller` (`Seller_Id`);
"""

alter_soldby2 = """
ALTER TABLE `SoldBy` ADD FOREIGN KEY (`Product_ItemID`) REFERENCES `Product` (`ItemId`);
"""

alter_deliveredto1 = """
ALTER TABLE `DeliveredTO` ADD FOREIGN KEY (`Customer_AccountID`) REFERENCES `Customer` (`Account_Id`);
"""

alter_deliveredto2 = """
ALTER TABLE `DeliveredTO` ADD FOREIGN KEY (`DeliveryPartner_UniqueID`) REFERENCES `DeliveryPartner` (`Unique_Id`);
"""

alter_delivery1 = """
ALTER TABLE `Delivery` ADD FOREIGN KEY (`Product_ItemID`) REFERENCES `Product` (`ItemId`);
"""

alter_delivery2 = """
ALTER TABLE `Delivery` ADD FOREIGN KEY (`DeliveryPartner_UniqueID`) REFERENCES `DeliveryPartner` (`Unique_Id`);
"""

alter_manages1 = """
ALTER TABLE `Manages` ADD FOREIGN KEY (`Administration_Username`) REFERENCES `Administration` (`Username`);
"""

alter_manages2 = """
ALTER TABLE `Manages` ADD FOREIGN KEY (`Customer_AccountID`) REFERENCES `Customer` (`Account_Id`);
"""

alter_manages3 = """
ALTER TABLE `Manages` ADD FOREIGN KEY (`Seller_SellerID`) REFERENCES `Seller` (`Seller_Id`);
"""

alter_manages4 = """
ALTER TABLE `Manages` ADD FOREIGN KEY (`Product_ItemID`) REFERENCES `Product` (`ItemId`);
"""

alter_paymentcredentials1 = """
ALTER TABLE `Payment_Credentials` ADD FOREIGN KEY (`Customer_Account_Id`) REFERENCES `Customer` (`Account_Id`);
"""

connection = create_db_connection("localhost", "root", pw, db)
execute_query(connection, alter_brand1)
execute_query(connection, alter_offer1)
execute_query(connection, alter_soldby1)
execute_query(connection, alter_soldby2)
execute_query(connection, alter_deliveredto1)
execute_query(connection, alter_deliveredto2)
execute_query(connection, alter_delivery1)
execute_query(connection, alter_delivery2)
execute_query(connection, alter_manages1)
execute_query(connection, alter_manages2)
execute_query(connection, alter_manages3)
execute_query(connection, alter_manages4)
execute_query(connection, alter_paymentcredentials1)




pop_product = """
INSERT INTO Product
VALUES ('1','Macbook Air','1', '0', '90000', 'Apple');
INSERT INTO Product
VALUES ('2','Parle-G','2', '0', '70', 'Parle');
INSERT INTO Product
VALUES ('3','Macbook Pro','3', '0', '135000', 'Apple');
INSERT INTO Product
VALUES ('4','Pixel 6','4', '0', '62000', 'Google');
INSERT INTO Product
VALUES ('5','Echo Studio','5', '0', '18000', 'Amazon');
"""

pop_seller = """
INSERT INTO Seller
VALUES ('1','Appario Retail');
INSERT INTO Seller
VALUES ('2','Anik');
INSERT INTO Seller
VALUES ('3','Cloudtail India');
INSERT INTO Seller
VALUES ('4','Amazon Pantry');
"""

pop_soldby = """
INSERT INTO SoldBy
VALUES ('1','1', '1');
INSERT INTO SoldBy
VALUES ('4','2','2');
INSERT INTO SoldBy
VALUES ('1','3', '3');
INSERT INTO SoldBy
VALUES ('2','4','4');
INSERT INTO SoldBy
VALUES ('3','5','5');
"""

pop_brand = """
INSERT INTO Brand
VALUES ('1','1','Apple');
INSERT INTO Brand
VALUES ('2','2','Parle');
INSERT INTO Brand
VALUES ('3','3','Apple');
INSERT INTO Brand
VALUES ('4','4','Google');
INSERT INTO Brand
VALUES ('5','5','Amazon');
"""

pop_offer = """
INSERT INTO Offer
VALUES ('1','1','11');
INSERT INTO Offer
VALUES ('2','2','0');
INSERT INTO Offer
VALUES ('3','3','5');
INSERT INTO Offer
VALUES ('4','4','10');
INSERT INTO Offer
VALUES ('5','5','20');
"""

pop_customer = """
INSERT INTO Customer
VALUES ('Manav','1','India','Uttar Pradesh', '202020');
INSERT INTO Customer
VALUES ('Amey','2','India','Gujarat', '202111');
INSERT INTO Customer
VALUES ('Harshavardhan','3','India','Meghalaya', '110033');
INSERT INTO Customer
VALUES ('Santiago','4','USA','Los Angeles', '646464');
INSERT INTO Customer
VALUES ('Fabian','5','Norway','Oslo', '777777');
INSERT INTO Customer
VALUES ('Smitty','6','Israel','Jerusalem', '999999');
"""

pop_paymentcredentials = """
INSERT INTO Payment_Credentials
VALUES ('1','34');
INSERT INTO Payment_Credentials
VALUES ('2','78');
INSERT INTO Payment_Credentials
VALUES ('3','47');
INSERT INTO Payment_Credentials
VALUES ('4','96');
INSERT INTO Payment_Credentials
VALUES ('5','49');
INSERT INTO Payment_Credentials
VALUES ('6','52');
"""

pop_administration = """
INSERT INTO Administration
VALUES ('Trevor Noah','MRKT', 'n.trev', 'xxxx');
INSERT INTO Administration
VALUES ('Jimmy Fallon','SPRT', 'f.jim', 'xxxx');
INSERT INTO Administration
VALUES ('Conan OBrian','SPRT', 'b.conan', 'xxxx');
INSERT INTO Administration
VALUES ('James Corden','MRKT', 'c.james', 'xxxx');
"""

pop_manages = """
INSERT INTO Manages
VALUES ('f.jim','4','1','1','1');
INSERT INTO Manages
VALUES ('b.conan','5','1','3','3');
INSERT INTO Manages
VALUES ('c.james','6','3','5','5');
"""

pop_deliverypartner = """
INSERT INTO DeliveryPartner
VALUES ('Passive','Fedex','Tom Cruise','1');
INSERT INTO DeliveryPartner
VALUES ('Active','DTDC','Jada','2');
INSERT INTO DeliveryPartner
VALUES ('Active','Fedex','Jamie Foxx','3');
INSERT INTO DeliveryPartner
VALUES ('Active','EKart','Javier','4');
"""

pop_delivery = """
INSERT INTO Delivery
VALUES ('1','1','2');
INSERT INTO Delivery
VALUES ('3','3','3');
INSERT INTO Delivery
VALUES ('5','5','4');

"""


pop_deliveredto = """
INSERT INTO DeliveredTO
VALUES ('2','4');
INSERT INTO DeliveredTO
VALUES ('3','5');
INSERT INTO DeliveredTO
VALUES ('4','6');
"""

connection = create_db_connection("localhost", "root", pw, db)

execute_query(connection, pop_product)
execute_query(connection, pop_seller)
execute_query(connection, pop_soldby)
execute_query(connection, pop_brand)
execute_query(connection, pop_offer)
execute_query(connection, pop_customer)
execute_query(connection, pop_paymentcredentials)
execute_query(connection, pop_administration)
execute_query(connection, pop_manages)
execute_query(connection, pop_deliverypartner)
execute_query(connection, pop_delivery)
execute_query(connection, pop_deliveredto)


def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
        print("Query successful")
    except Error as err:
        print(f"Error: '{err}'")

def read_query(connection, query):
    cursor = connection.cursor()
    result = None
    try:
        cursor.execute(query)
        result = cursor.fetchall()
        return result
    except Error as err:
        print(f"Error: '{err}'")

connection = create_db_connection("localhost", "root", pw, db)

def queryprocessor(n):
    exit()

def functionprocessor(ch1):
 if ch1 >0 and ch1 < 5:
     while(1):
                # Here taking example of Employee Mini-world
                print("1 - Product")  
                print("2 - Admin")  
                print("3 - Seller")  
                print("4 - Delivery")
                print("5 - EXIT")
                operation = int(input("Enter number corresponding to choice> "))
                if operation ==1:
                    table = "Product"
                if operation ==2:
                    table = "Admin"
                if operation ==3:
                    table = "Seller"
                if operation ==4:
                    table = "Delivery"

                if operation == 5:
                    exit()
                else:
                    #call for queries
                    #remove exit below
                    #removed the section where we called the queries because of errors

                    #idea is to assign a number to queries and call the queryprocessor function to execute


                    exit()     
 else:
     print("Error.Start again")
     exit()

while(1):
        con = mysql.connector.connect(host='localhost',
                              port=30306,
                              user="root",
                              password="abcde",
                              db='Logistics',
                              cursorclass=mysql.connector.DictCursor)

        if(con.open):
            print("Connected")
        else:
            print("Failed to connect")

        tmp = input("Enter any key to CONTINUE>")

        with con.cursor() as cur:
            while(1):
                # Here taking example of Employee Mini-world
                print("1 - CREATE")  # Hire an Employee
                print("2 - READ")  # Fire an Employee
                print("3 - UPDATE")  # Promote Employee
                print("4 - DELETE")  # Employee Statistics
                print("5 - EXIT")
                ch1 = int(input("Enter number corresponding to choice> "))
                if ch1 == 5:
                    exit()
                else:
                    functionprocessor(ch1)
                    tmp = input("Enter any key to CONTINUE>")