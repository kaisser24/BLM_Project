from flask import *
from digi.xbee.devices import XBeeDevice
import serial
# from flask_sqlalchemy import *
# from flask_login import LoginManager, UserMixin, login_user, logout_user, current_user, login_required

app = Flask(__name__)
# app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///shoedatabase.sqlite'
# db = SQLAlchemy(app)

# app.app_context().push()


# app.config['SECRET_KEY'] = 'whatAnAmazingSecretKey!!'
# login_manager = LoginManager(app)
# login_manager.init_app(app)

#look for com port for Xbee

@app.route('/view_data')
def view_data():
    return render_template('view_data.html')

#read and display message from comPort
def getData():
    comPort = None
    try:
        comPort = serial.Serial("COM4", 9600)
        print("com port established")
    except Exception as e:
        print("Error: ", e)
        return
    # user_in = "t" + "\n"
    # comPort.write(user_in.encode())
    while True: 
        if comPort is not None:
            print("made it here")
            msg = comPort.readline()
            if(msg != ""):
                msg = str(msg)
                msg = msg.strip("b'\r\n")
                print("From Arduino: " + msg)

if __name__ == '__main__':
    #db.create_all()
    getData()
    #app.run()
    

