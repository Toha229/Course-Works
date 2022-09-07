using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Quizes
{
    class Tab
    {
        protected int option = 0;
        public List<string> options = null;
        public Tab() { }
        public Tab(List<string> Options)
        {
            options = Options;
        }
        public int Print()
        {
            for(int i = 0; i < options.Count; i++)
            {
                if (option == i) Console.Write(">");
                Console.WriteLine($"\t{options[i]}");
            }
            while (true)
            {
                switch (Console.ReadKey(true).Key)
                {
                    case ConsoleKey.W: case ConsoleKey.UpArrow:
                        this.Up();
                        break;

                    case ConsoleKey.S: case ConsoleKey.DownArrow:
                        this.Down();
                        break;

                    case ConsoleKey.Enter:
                        return Select();
                }
            }
        }
        public void Up()
        {
            if(option > 0)
            {
                Console.SetCursorPosition(0, option);
                Console.WriteLine(" ");
                option--;
                Console.SetCursorPosition(0, option);
                Console.WriteLine(">");
                Console.SetCursorPosition(0, options.Count);
            }
        }
        public void Down()
        {
            if (option < options.Count - 1)
            {
                Console.SetCursorPosition(0, option);
                Console.WriteLine(" ");
                option++;
                Console.SetCursorPosition(0, option);
                Console.WriteLine(">");
                Console.SetCursorPosition(0, options.Count);
            }
        }
        public int Select()
        {
            return option;
        }
    }
    //class LoginPage : Tab
    //{
    //    public LoginPage()
    //    {
    //        options.Add("Login");
    //        options.Add("Register");
    //    }
    //    public void Select()
    //    {
    //        switch(option)
    //        {
    //            case 0:
    //                {
                        
    //                }
    //        }
    //    }
    //}
}
