# detPole - Andre Brandao, Emanuel Pereira, Tiago Lima
# File to insert data into database
# File format must be csv:
# First line (Company): Company, company name
# Next Lines (Users): Name, RFID, Contact, email, Citizen, Address, Birthdate

import csv
import pymysql

Host = "localhost" 		# IP address of the MySQL database server  
User = "detpole"		# User name of the database server   
Password = "detpole"	# Password for the database user      
  
Database = "users_dock"	# Database Name

# Connect to database
conn  = pymysql.connect(host=Host, user=User, password=Password, database=Database) 

# Create a cursor object 
cur  = conn.cursor() 

print("""Is a new company:
1 - Yes
2 - No
Option?""")

confirmation = input()

if confirmation != "1" and confirmation != "2":
	print('Option number unavailable!')
	print('Exiting...')
	exit() 

print("""\nAvailable options:
1 - Read from csv file
2 - Write a new user
3 - Exit
Option?""")

num = input()

if num != "1" and num != "2" and num != "3":
	print('Option number unavailable!')
	print('Exiting...')
	exit() 

if num == "1":
	while True:
		print('Name of file?')
		file_name = input()
		
		try:	# if file exists open if not ask name of file again
			with open(file_name) as csv_file:
				csv_reader = csv.reader(csv_file, delimiter=',')

				line = 0
				for row in csv_reader:
					if line == 0:
						try:	# First line (company definition) with errors abort
							company = row[1]
						
						except IndexError as error:
							print(f'Line {line+1} with errors nothing inserted into database')
							exit()
						
						if confirmation == "1":		# If inserting new company create company table
							query=f"CREATE TABLE {company}(id int(8) AUTO_INCREMENT PRIMARY KEY NOT NULL,name TINYTEXT NOT NULL,rfid TINYTEXT NOT NULL,contact TINYTEXT NOT NULL,email TINYTEXT NOT NULL,citizen TINYTEXT NOT NULL,address TINYTEXT NOT NULL,birth TINYTEXT NOT NULL);"
							cur.execute(query)
							conn.commit()
						
						elif confirmation == "2":	# If updating company table
							query=f"DELETE FROM {company}"	# empty table
							cur.execute(query)
							conn.commit()

							query=f"ALTER TABLE {company} AUTO_INCREMENT = 1;"	# Correct ID number
							cur.execute(query)
							conn.commit()

						line += 1
					
					else:	# Insert user
						try:	# Lines with formating errors not inserted
							query = f"INSERT INTO {company}(name,rfid,contact,email,citizen,address,birth) VALUES ('{row[0]}','{row[1]}','{row[2]}','{row[3]}','{row[4]}','{row[5]}','{row[6]}')"
							cur.execute(query)
							conn.commit()
							line += 1
								
						except IndexError as error:
							print(f'Line {line+1} with errors on csv not inserted into database')
							line += 1
							continue
				print('Done!')
				break

		except FileNotFoundError as error:
			print("\nFile Not Found!")
			continue	
					
elif num == "2":
	print("Company?")
	company = input()

	if confirmation == "1":		# If inserting new company create company table
		query=f"CREATE TABLE {company}(id int(8) AUTO_INCREMENT PRIMARY KEY NOT NULL,name TINYTEXT NOT NULL,rfid TINYTEXT NOT NULL,contact TINYTEXT NOT NULL,email TINYTEXT NOT NULL,citizen TINYTEXT NOT NULL,address TINYTEXT NOT NULL,birth TINYTEXT NOT NULL);"
		cur.execute(query)
		conn.commit()
	
	print("\nName?")
	name = input()
	print("\nRFID?")
	rfid = input()
	print("\nContact?")
	contact = input()
	print("\nEmail?")
	email = input()
	print("\nCitizen?")
	citizen = input()
	print("\nAddress?")
	address = input()
	print("\nBirth?")
	birth = input()
	
	# Insert user
	query = f"INSERT INTO {company}(name,rfid,contact,email,citizen,address,birth) VALUES ('{name}','{rfid}','{contact}','{email}','{citizen}','{address}','{birth}')"	
	cur.execute(query)
	conn.commit()
	
	print(f'User ({name},{rfid},{contact},{email},{citizen},{address},{birth}) inserted in {company}')

elif num == "3":
	print('Exiting...')
	exit()

# Close connection to database
conn.close()
