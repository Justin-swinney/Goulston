# Goulston

Goulston Technologies requested I evaluate their current process for implementing and removing employee photos from a locally run IIS server.

Goulston’s Original Process:

-	HR department would crop the image and send the cropped image to the IT department.
-	The IT department would then place the image in a folder and manual add a premade HTML table code around 15 lines into an HTML document.
-	The new code added would be manually placed in alphabetical order by the IT department.
-	To remove a photo the IT department would be notified, and the code would be manually removed from the HTML file. 

Goulston New Process:

-	HR will crop an image and name the image.
-	The backend code will automatically detect any changes within the folder and add the new image into a new table cell automatically.
-	I also implemented a search feature for the website as well as a time stamp for any changes made to the website.

NOTE:
-	During the original designing of the new process, I created a C++ / QT desktop application that would allow HR to add images, remove images, rename images as well as cropping images without the need to interact with a folder to avoid accidentally removing images I implemented confirmations to ensure the actions within the application were desired and not accidental. This idea was scratched as their current cropping method for creating ID badges is already in place and the newly created desktop application would create more work for the HR department. Overall it was a great learning experience interacting with a desktop interface. Learning the fundematals of an IIS server and setting one up locally at home that supported PHP. 
