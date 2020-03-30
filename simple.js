function validateForm() {
	var empty = "";
	var warn ="";
	var rt = true;
	var str_user_inputs = "";
	
	// Email
	var email = document.forms.SignUp.email.value;
	
	if (email == null || email =="") {
		empty += " * Email:\n";
		rt = false;
		
	}
	else if (email.length > 60) {
		warn += "Email must be less than 60 characters long.\n";
		rt = false;
		
	}
	else {
		str_user_inputs += "Email: " + email + "\n";
	}
	
	// Username
    var username = document.forms.SignUp.username.value;
	
	if (username == null || username =="") {
		empty += " * Username:\n";
		rt = false;
		
	}
	else if (username.length > 40) {
		warn += "Username must be less than 40 characters long.\n";
		rt = false;
		
	}
	else {
		str_user_inputs += "Username: " + username + "\n";
	}
	
	// Password
    var password = document.forms.SignUp.password.value;
	
	if (password == null || password =="") {
		empty += " * Password:\n";
		rt = false;
		
	}
	else if (password.length != 8) {
		warn += "Password has to be 8 characters long!\n";
		rt = false;
	}
	else {
		str_user_inputs += "Password: " + password + "\n";
	}

	
	// Confirm password
    var confirmpassword = document.forms.SignUp.confirmpassword.value;
	
	if (confirmpassword == null || confirmpassword == "") {
		empty += " * Confirm password:\n";
		rt = false;	
	}
	else if (confirmpassword != password) {
		warn += "Confirmed password does not match the password entered.\n";
		rt = false;
	}
	else {
		str_user_inputs += "Confirm password: " + confirmpassword + "\n";
	}
	
	// Alert messages
	if (rt == false){
		var message = "";
		if (empty != "")
			{
			message += "The following fields must be filled out:\n" + empty + "\n";
			}
		if (warn != "")
			{
			message += "Please also fix the following errors:\n" + warn + "\n";
			}
		alert(message);
		return false;
	}
	else {
		alert(str_user_inputs);
		return false;
	}
	
}
