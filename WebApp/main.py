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


@app.route('/')
def home():
    return render_template('home.html')

@app.route('/create_user')
def create_user():
    return render_template('create_user.html')

@app.route('/manage_users')
def manage_users():
    return render_template('manage_users.html')

@app.route('/view_data')
def view_data():
    return render_template('view_data.html')
#read and display message from comPort

@app.route('/get_data')
def get_data():
    fetchData = getData()
    return render_template('get_data.html', fetchData=fetchData)

def getData():
    comPort = None
    try:
        comPort = serial.Serial("COM5", 9600)
        print("com port established")
    except Exception as e:
        print("Error: ", e)
        return None
    # Send a signal to the Arduino to start transmission
    comPort.write(b't')
    data_list = []
    while True:
        #receieve initial arduino message
        msg = comPort.readline().strip().decode()
        if msg:
            # 'start' indicates the arduino has data
            if msg == "start":
                # read in data stored in arduino
                while True:
                    msg = comPort.readline().strip().decode()
                    if msg == "end":
                        break
                    data_list.append(msg)
                    print("From Arduino: " + msg)
                break
            # 'none' indicates arduino does not have stored data
            elif msg == 'none':
                print("No data stored in Arduino")
                break

    return data_list

if __name__ == '__main__':
    #db.create_all()
    app.run()


