import os
import shutil
import zipfile
import subprocess

'''
This script compiles the app folder into a zip file,
so the engine can run it, after compilation it runs the program
'''

def compile() -> None:
    # Define the app folder and zip file name
    app_folder = "app"
    zip_filename = "app.zip"
    
    # Check if the app folder exists
    if not os.path.exists(app_folder):
        print(f"The folder '{app_folder}' does not exist.")
        return

    # Check if app.zip exists and delete it if it does
    if os.path.exists(zip_filename):
        print(f"Deleting existing '{zip_filename}'...")
        os.remove(zip_filename)
    
    # Create a new zip file
    print(f"Creating '{zip_filename}'...")
    with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
        # Walk through the app folder
        for root, dirs, files in os.walk(app_folder):
            for file in files:
                file_path = os.path.join(root, file)
                # Add the file to the zip file under the app/ directory
                zipf.write(file_path, os.path.relpath(file_path, os.path.join(app_folder, '..')))
    
    print(f"'{zip_filename}' created successfully.")

def run() -> None:
    subprocess.run("game.exe")

if __name__ == "__main__":
    compile()
    run()
