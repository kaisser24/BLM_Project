from flask import *
# from flask_sqlalchemy import *
# from flask_login import LoginManager, UserMixin, login_user, logout_user, current_user, login_required

app = Flask(__name__)
# app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///shoedatabase.sqlite'
# db = SQLAlchemy(app)

# app.app_context().push()


# app.config['SECRET_KEY'] = 'whatAnAmazingSecretKey!!'
# login_manager = LoginManager(app)
# login_manager.init_app(app)

@app.route('/view_data')
def view_data():
    return render_template('view_data.html')

if __name__ == '__main__':
    #db.create_all()
    app.run()