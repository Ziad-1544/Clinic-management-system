# Clinic Management System

## Main Menu:
-Display welcome message and user modes (Admin, Secretary, Patient, Exit)
###User selects a mode:
#### Admin Mode:
Prompt for admin passcode (up to 3 attempts)<br>
If correct, set admin flag to 1
#### Display admin options:
-Create secretary profile<br>
-Create patient profile<br>
#### User selects an option

### Secretary Mode:
-Check if secretary account exists<br>
If not, display error message and exit<br>
Prompt for secretary passcode (up to 3 attempts)<br>
If correct, set secretary flag to 1<br>

#### Display secretary options:
-Accept all pending requests<br>
-Clear all requests<br>
-Show today's reservations<br>
-Search for specific patient record<br>
-Edit slot status<br>
-Add patient history<br>
-Delete patient profile<br>
#### User selects an option:
-Accept all pending requests: call requests_orders() function with argument 1<br>
-Clear all requests: call requests_orders() function with argument 2<br>
-Show today's reservations: call show_today_slots() function Search for specific patient record: call view_patient() function<br>
-Edit slot status: call edit_slot() function<br>
-Add patient history: call add_pat_history() function<br>
-Delete patient profile: call delete_pat() function<br>

### Patient Mode:
#### Display patient options:
-Log in<br>
-Sign up
#### User selects an option:
-Log in: call logn_in_pat() function<br>
-Sign up: call sign_up_pat() function

### Exit:
Display shutdown message and exit program

## Functions:

### Admin Functions

-admin_acces(): prompt for admin passcode and set admin flag to 1 if correct<br>
-admin_acces_denied(): check if admin flag is set to 0 and exit program if true<br>
-sign_up_secretary(): create a new secretary profile<br>
-sign_up_pat(): create a new patient profile

### Secretary Functions

-secretary_acces(): prompt for secretary passcode and set secretary flag to 1 if correct<br>
-secretary_acces_denied(): check if secretary flag is set to 0 and exit program if true<br>
-requests_orders(): accept or clear all pending requests<br>
-show_today_slots(): display today's reservations<br>
-view_patient(): display a patient's profile and history<br>
-edit_slot(): edit a slot's status and patient ID<br>
-add_pat_history(): add a new record to a patient's history<br>
-delete_pat(): delete a patient profile

### Patient Functions

-logn_in_pat(): prompt for patient ID and check if it exists in the system<br>
-post_login_pat(): display patient options:
-View history
-Request a visit
-view_history(): display a patient's history
-request_slots(): display available slots and prompt patient to choose one

