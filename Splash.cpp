#include "Splash.h"
int Splash::n = 0;
#define BTN_S 3 //spacing
#define ORIGIN_X 130 //first button X
#define ORIGIN_Y 300 //first button Y
#define BTN_LEN  500

struct loginData {

};

//BUTTON PARAM STORAGE
struct Button
{
public:
	int x, y, fontsize;
	string name;
};



Splash::Splash()
{
	this->userLoggedIn = false;
	this->dead = false;
	/////////////////////////////////////
	//...........INITIALIZATION........//
	/////////////////////////////////////
	loadAssets();
	buttonAnimations();

	//Text Data Initialization
	Button b[MENU_ELEMENTS] = { { 50,100,20,"WELCOME" },
							{ 130, 330, /*b[0].size*/45, "PLAY NOW!" },
							{ 130, 400, b[1].fontsize, "LOGIN" },
							{ 130, 470, b[2].fontsize, "REGISTER" },
							{ 130, 540, b[3].fontsize, "EXIT" },
							{ 600, 100, b[0].fontsize, "NEXT" },
							{ 50, 145, 13, "" } };
	

	//TIME DEALY
	Clock mainClock;
	float timeDelay = 2;
	
	bool coordinatesshow	= true;
	bool exitOnDealy		= false;
	bool startTextEntry		= false;
	bool showSubmitButton	= false;
	bool editSubmitButton	= false;
	bool newUserSignUp		= false;
	int submitBtnClicks		= -1;

	////TEXT ENTRY
	/*dataEntryE[0] = "1.Email = ";
	dataEntryE[2] = "2.Email = ";
	dataEntryE[1] = "1.PASSWORD = ";
	dataEntryE[3] = "2.PASSWORD = ";*/

	//POSITIONING OF THE BUTTONS AND TEXT WITHIN
	for (int i = 0; i < MENU_ELEMENTS; i++) {
		setText(i, b[i].name, &a_gc, b[i].x+15, b[i].y, b[i].fontsize);
		btnActive[i].setPosition(b[i].x - 20, b[i].y);
		btnInactive[i].setPosition(b[i].x - 20, b[i].y);
	}
	setText(6, b[6].name, &a_gc, b[6].x + 15, b[6].y, b[6].fontsize);

	system("color 4F");
	///////WINDOW LOOP/////////
	while (splash.isOpen()) {

		float timeNow = mainClock.getElapsedTime().asSeconds();
		Vector2i mouseTrack = Mouse::getPosition(splash);
		Event e;

		while (splash.pollEvent(e)) {

			splash.clear();
			splash.draw(paintBG);				

			/*if (coordinatesshow) {
				system("cls");
				cout << to_string(mouseTrack.x) + " , " + to_string(mouseTrack.y) << endl;
				//allText[0].setString(to_string(mouseTrack.x) + " , " + to_string(mouseTrack.y));
			}*/

			////////INITIAL BUTTON DRAWING
			for (int i = 0; i < MENU_ELEMENTS; i++) {
				splash.draw(btnActive[i]);
				splash.draw(allText[i]);
			}

			///////////ON-HOVER ANIMATION////////////
			if (e.type == Event::MouseMoved) {

				for (int i = 0; i < MENU_ELEMENTS; i++) {
					if (btnActive[i].getGlobalBounds().contains(mouseTrack.x, mouseTrack.y)) {
						splash.draw(btnInactive[i]);
						splash.draw(allText[i]);
					}
				}

			}

			////FOR SUBMIT BUTTON
			if (showSubmitButton && editSubmitButton) {
				setText(5, b[5].name, &a_gc, b[5].x + 15, b[5].y + 7, b[5].fontsize);
				btnActive[5].setPosition(b[5].x - 5, b[5].y);
				btnInactive[5].setPosition(b[5].x - 5, b[5].y);
				submitBtn();
			}

			//////////ON CLICK FUNCTIONS
			if (e.type == Event::MouseButtonPressed) {
			//for (int i = 0; i < MENU_ELEMENTS; i++) {

			/////BUTTON 1 FUNCTION/////////
				if (btnActive[1].getGlobalBounds().contains(mouseTrack.x, mouseTrack.y)) {
						
					timeDelay = 0;
					exitOnDealy = this->dead = true;
				}


			///////BUTTON 2 FUNCTION////////
				if (btnActive[2].getGlobalBounds().contains(mouseTrack.x, mouseTrack.y)) {

					if (!startTextEntry) {
						coordinatesshow = false;
						startTextEntry = showSubmitButton = editSubmitButton = true;
						//submitBtnClicks++;
						loginPressed(submitBtnClicks);
					}

				}

				if (btnActive[3].getGlobalBounds().contains(mouseTrack.x, mouseTrack.y)) {

					if (!startTextEntry) {
						coordinatesshow = false; newUserSignUp = true;
						startTextEntry = showSubmitButton = editSubmitButton = true;
						submitBtnClicks+=2; //email at 2, pass at 3
						loginPressed(submitBtnClicks);
						cout << "registeration";
					}
				}

				if (btnActive[4].getGlobalBounds().contains(mouseTrack.x, mouseTrack.y)) {
					//////////BUTTON 4 FUNCTION//////////////
					coordinatesshow = false; exitOnDealy = true;
					timeDelay = timeNow + 2;

					updText(0, "Thank You! See You Soon");
					allText[0].setFont(b_et);
							
				}

				if (btnActive[5].getGlobalBounds().contains(mouseTrack.x, mouseTrack.y)) {
						editSubmitButton = showSubmitButton = false;
						accountDecision(submitBtnClicks, newUserSignUp, startTextEntry);
						if (submitBtnClicks == 3)
							updText(5, "SUBMIT");
				}
			//}
			}

			////TEXT INPUT FUNCTION////
			if (e.type == Event::TextEntered && startTextEntry) {
				system("cls");
				//if (submitBtnClicks > 0) {
				string* s = &dataEntryE[submitBtnClicks];
				string temp = *s;

				if (e.text.unicode != 8 && e.text.unicode != 13)
					temp += (char)e.text.unicode;
				else {
					if (temp.size() > 0 && e.text.unicode == 8)
						temp = temp.substr(0, temp.size() - 1);
					if (e.text.unicode == 13)
						accountDecision(submitBtnClicks, newUserSignUp, startTextEntry);
				}


				cout << e.text.unicode << endl;
				cout << temp;
				*s = temp;
				updText(0, *s);
			}
			
			splash.display();
		}



		////////EXIT CONTROLLER
		if (exitOnDealy) {
				
			if (timeDelay == 0) {
				splash.close();
			} else if (timeNow >= timeDelay) {
				splash.close();
				exit(1);
			}
		}
	}

	system("color 0F");
}




void Splash::setText(int no , string in , Font* ft, int posX , int posY , int size ) {
	allText[no].setFont(*ft);
	//textContent[no] = in;
	allText[no].setString(in);
	allText[no].setCharacterSize(size);
	allText[no].setPosition(posX, posY);
}

void Splash::updText(int no, string in) {
	//textContent[no] = in;
	allText[no].setString(in);
}

Splash::~Splash()
{
}
//ASSETS LOADING
void Splash::loadAssets() {
	//FONTS & BACKGROUNDS///
	a_gc.loadFromFile("fonts/a_gc.ttf");
	b_et.loadFromFile("fonts/b_et.ttf");
	img.loadFromFile(SPLASH_BG_LOCATION);
	splash.create(SPLASH_ATTR);
	btnTexture.loadFromFile("images/buttons.png");
	paintBG.setTexture(img);
}
//BUTTON TEXTURING 
void Splash::buttonAnimations() {

	for (int i = 0; i < MENU_ELEMENTS - 2; i++) {
		//cout << "texture set";
		btnActive[i].setTextureRect(IntRect(0, 0, BTN_LEN, 55 + BTN_S));
		//if (i!=0) 
		btnActive[i].setTexture(btnTexture);
		btnActive[i].setColor(sf::Color(0, 0, 0, 100));

		btnInactive[i].setTextureRect(IntRect(0, 200, BTN_LEN, 55 + BTN_S));
		if (i != 0) btnInactive[i].setTexture(btnTexture);
		btnInactive[i].setColor(sf::Color(250, 0, 0, 150));
	}

	btnActive[0].setColor(sf::Color(0, 0, 0, 0));
}

void Splash::loginPressed(int& clicks) {
	//updText(0, "");
	switch (clicks) {
	case -1:
		updText(6, "[Player1] Please Enter Your Username / Email");
		break;
	case 0:
		updText(6, "[Player1] Please Enter Your Password");
		break;
	case 1:
		updText(6, "[Player2] Please Enter Your Username / Email");
		break;
	case 2:
		updText(6, "[Player2] Please Enter Your Password");
		break;
	}
	if (clicks < 3)
		clicks++;
	//if (clicks > 3)
		//updText(5, "X");
}

void Splash::submitBtn() {
	btnActive[5].setTextureRect(IntRect(0, 0, 200, 40));
	btnActive[5].setTexture(btnTexture);
	btnInactive[5].setTextureRect(IntRect(0, 200, 200, 40));
	btnInactive[5].setTexture(btnTexture);

	allText[0].setPosition(50, 107);
	btnActive[0].setTextureRect(IntRect(0, 200, 700, 40));
	btnActive[0].setColor(sf::Color(250, 0, 0, 100));
}

void Splash::validate(int &hits) {
	int index;
	string mail, pass;

	switch (hits) {
	case 0:
	case 2:
		mail = dataEntryE[hits];
		pass = "x";
		break;
	case 1:
	case 3:
		mail = dataEntryE[hits - 1];
		pass = dataEntryE[hits];
		break;
	}

	index = data.email_search(mail);

	if (pass == "x") {
		if (index == -1) { //mail not found
			updText(0, "Invalid Email Entered!");
			dataEntryE[hits] == " ";
		}
		else { //mail found
			updText(0, "...");
			loginPressed(hits);
		}
	}
	else {
		if (data.password_check(index, pass)) {
			loginPressed(hits);
			
			int x = (hits == 2) ? 1 : 0;

			all[0].side = "black";
			all[1].side = "white";
			all[x].mail = mail;
			all[x].pass = pass;
			all[x].index = index;
			
			playingSideIndex[x] = index;

			updText(0, "Login SuccessFul! - " + all[x].side);

			if (hits > 2) {
				updText(6, "Click Play to start game...");
				userLoggedIn = true;
			}
			
			
		}
		else {
			dataEntryE[hits] == " ";
			updText(0, "Password Incorrect! Try Again");
		}
	}


}

void Splash::accountDecision(int &hits, bool flag, bool &flag2) {
	if (hits < 4) {
		if (flag)
			signup(hits);
		else
			validate(hits);
	}

	else {
		hits = -1;
		flag2 = false;
		updText(0, "...");
		updText(5, "DONE!");
		updText(6, "LOGIN MESSAGE GOES HERE");
	}

}

void Splash::signup(int &hits) {

	switch (hits) {
	case 2:
		loginPressed(hits);
		updText(0, "...");
		//mail
		break;
	case 3:
		data.new_account(dataEntryE[hits - 1], dataEntryE[hits]);
		loginPressed(hits);
		updText(0, "Rrgisteration SuccessFul!");
		updText(6, "You can now login ... ");
		hits = -1;
		//pass
		break;
	}



}


