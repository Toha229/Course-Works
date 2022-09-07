using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Quizes
{
    class User
    {
        private string login;
        private string pass;
        public string Login {
            get => login;
            set
            {
                if (!string.IsNullOrWhiteSpace(value))
                {
                    login = value;
                }
                else throw new Exception("Login is empty");
            }
        }
        public string Pass { 
            get => pass;
            set
            {
                if(value == null || value.Length < 6 || value.Length > 16)
                {
                    throw new Exception("Password must be 6 - 16 characters long");
                }
                pass = value;
            }
        }
        public DateTime Birthdate { get; set; }
        public User() { }
        public User(string login, string pass, DateTime birthdate)
        {
            Login = login;
            Pass = pass;
            Birthdate = birthdate;
        }
    }
}
