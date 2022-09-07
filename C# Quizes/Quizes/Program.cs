using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Quizes
{
    class Program
    {
        static void Main(string[] args)
        {
            string userList = "users.json";
            string quizList = "quizes.json";
            User client = null;
            //client = new User();
            //client.Login = "Toha229";
            Tab loginPage = new Tab(new List<string>() { "Login", "Register", "Exit"});
            while (client == null)
            {
                string login;
                string pass;
                switch (loginPage.Print())
                {

                    case 0:
                        //LOGIN
                        Console.Clear();
                        Console.Write("Input login: ");
                        login = Console.ReadLine();
                        Console.Write("Input pass: ");
                        pass = Console.ReadLine();
                        if (File.Exists(userList))
                        {
                            var result = JsonConvert.DeserializeObject<List<User>>(File.ReadAllText(userList));
                            foreach (var item in result)
                            {
                                if (item.Login == login && item.Pass == pass)
                                {
                                    client = item;
                                    Console.WriteLine("You have successfully logined!");
                                    Console.ReadKey(true);
                                    Console.Clear();
                                    break;
                                }
                            }
                        }
                        if (client == null)
                        {
                            Console.WriteLine("Wrong login or pass");
                            Console.ReadKey(true);
                            Console.Clear();
                        }
                        break;

                    case 1:
                        //REGISTER
                        Console.Clear();
                        Console.Write("Input login: ");
                        login = Console.ReadLine();
                        if (File.Exists(userList))
                        {
                            if (JsonConvert.DeserializeObject<List<User>>(File.ReadAllText(userList)).FindIndex(u => u.Login == login) != -1)
                            {
                                Console.WriteLine("This login is already taken!");
                                Console.ReadKey(true);
                                Console.Clear();
                                break;
                            }
                        }

                        client = new User();
                        try
                        {
                            client.Login = login;
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex);
                            client = null;
                            Console.ReadKey(true);
                            Console.Clear();
                            break;
                        }
                        Console.Write("Input pass: ");
                        pass = Console.ReadLine();
                        try
                        {
                            client.Pass = pass;
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex);
                            client = null;
                            Console.ReadKey(true);
                            Console.Clear();
                            break;
                        }
                        try
                        {
                            Console.Write("Input day of birthdate: ");
                            int day = int.Parse(Console.ReadLine());
                            Console.Write("Input month of birthdate: ");
                            int month = int.Parse(Console.ReadLine());
                            Console.Write("Input year of birthdate: ");
                            int year = int.Parse(Console.ReadLine());
                            client.Birthdate = new DateTime(year, month, day);

                            List<User> users = new List<User>();
                            if (File.Exists(userList))
                            {
                                users = JsonConvert.DeserializeObject<List<User>>(File.ReadAllText(userList));
                            }
                            users.Add(client);
                            File.WriteAllText(userList, JsonConvert.SerializeObject(users));
                            Console.WriteLine("You have successfully registered!");
                        }
                        catch(Exception ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                        Console.ReadKey(true);
                        Console.Clear();
                        break;

                    case 2:
                        //EXIT
                        Console.Clear();
                        return;
                }
            }




            Tab menu = new Tab(new List<string>() { "Classic", "Mixed mode", "Last results", "Score board", "Edit account", "Editing mode", "Exit"});
            Tab Classic = new Tab();
            Tab EMode = new Tab(new List<string>() { "Create quiz","Edit question", "Delete quiz", "Back"});
            while (true)
            {
                switch (menu.Print())
                {
                    case 0:
                        //CLASSIC
                        Console.Clear();
                        if (File.Exists(quizList))
                        {
                            List<Quiz> quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                            foreach (var item in quizes)
                            {
                                Console.WriteLine(item + "\n");
                            }
                            Console.WriteLine("Input name of quiz:");
                            string qname = Console.ReadLine();
                            int q = quizes.FindIndex(qu => qu.Name == qname);
                            if (q == -1)
                            {
                                Console.WriteLine("Quize is not exist!");
                            }
                            else
                            {
                                Console.Clear();
                                quizes[q].Start(client.Login);
                                File.WriteAllText(quizList, JsonConvert.SerializeObject(quizes));
                            }
                        }
                        else
                        {
                            Console.WriteLine("Quizes not found :(");
                        }
                        Console.ReadKey(true);
                        Console.Clear();
                        break;

                    case 1:
                        {
                            //MIXED MODE
                            Console.Clear();
                            if (File.Exists(quizList))
                            {
                                var quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                                Random rnd = new Random();
                                int i = 0;
                                int mark = 0;
                                while (i < 20)
                                {
                                    int r = rnd.Next(0, quizes.Count);
                                    int r2 = rnd.Next(0, quizes[r].Questions.Count);
                                    if (quizes[r].Questions[r2].mark == -1)
                                    {
                                        Console.Write((i + 1) + "/20 ");
                                        mark += quizes[r].Questions[r2].Ask();
                                        i++;
                                        Console.Clear();
                                    }
                                }
                                Console.WriteLine($"Your mark: {mark}/20");
                            }
                            else
                            {
                                Console.WriteLine("Quizes not found :(");
                            }
                            Console.ReadKey(true);
                            Console.Clear();
                            break;
                        }
                    case 2:
                        //LAST RESULTS
                        {
                            Console.Clear();
                            List<Quiz> quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                            bool lr = false;
                            foreach(var item in quizes)
                            {
                                for (int i = 0; i < item.ScoreBoard.Count; i++)
                                {
                                    if(item.ScoreBoard[i].Item2 == client.Login)
                                    {
                                        Console.ForegroundColor = ConsoleColor.DarkYellow;
                                        if(i == 0)
                                        {
                                            Console.ForegroundColor = ConsoleColor.Green;
                                        }
                                        Console.WriteLine($"{item}\nPlace: {i + 1}. Mark: {item.ScoreBoard[i].Item1}\n");
                                        Console.ForegroundColor = ConsoleColor.Gray;
                                        lr = true;
                                    }
                                }
                            }
                            if (!lr)
                            {
                                Console.WriteLine("You have no results yet :(");
                            }
                            Console.ReadKey(true);
                            Console.Clear();
                            break;
                        }
                    case 3:
                        {
                            //SCORE BOARD
                            Console.Clear();
                            List<Quiz> quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                            foreach (var item in quizes)
                            {
                                Console.WriteLine(item + "\n");
                            }
                            Console.WriteLine("Input name of quiz:");
                            string qname = Console.ReadLine();
                            int q = quizes.FindIndex(qu => qu.Name == qname);
                            if (q == -1)
                            {
                                Console.WriteLine("Quize is not exist!");
                            }
                            else
                            {
                                Console.Clear();
                                quizes[q].ScoreBoardPrint();
                            }
                            Console.ReadKey(true);
                            Console.Clear();
                            break;
                        }
                    case 4:
                        //EDIT ACCOUNT
                        Console.Clear();
                        var users = JsonConvert.DeserializeObject<List<User>>(File.ReadAllText(userList));
                        int cindex = users.FindIndex(u => u.Login == client.Login);
                        Console.Write("Input new pass: ");
                        string pass = Console.ReadLine();
                        try
                        {
                            client.Pass = pass;
                            users[cindex].Pass = pass;
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex);
                            Console.ReadKey(true);
                            Console.Clear();
                            break;
                        }
                        try
                        {
                            Console.Write("Input new day of birthdate: ");
                            int day = int.Parse(Console.ReadLine());
                            Console.Write("Input new month of birthdate: ");
                            int month = int.Parse(Console.ReadLine());
                            Console.Write("Input new year of birthdate: ");
                            int year = int.Parse(Console.ReadLine());
                            client.Birthdate = new DateTime(year, month, day);
                            users[cindex].Birthdate = new DateTime(year, month, day);

                            File.WriteAllText(userList, JsonConvert.SerializeObject(users));
                            Console.WriteLine("Your profile has been edited!");
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                        Console.ReadKey(true);
                        Console.Clear();
                        break;


                    case 5:
                        //EDITING MODE
                        Console.Clear();
                        switch (EMode.Print())
                        {
                            case 0:
                                {
                                    //CREATE QUIZ
                                    Console.Clear();
                                    Console.Write("Input theme of quiz: ");
                                    string subject = Console.ReadLine();
                                    Console.Write("Input name of quiz: ");
                                    string name = Console.ReadLine();
                                    Quiz quiz = new Quiz(name, subject, client.Login);
                                    while (quiz.Questions.Count < 20)
                                    {
                                        Console.WriteLine($"Input {quiz.Questions.Count + 1} question: ");
                                        quiz.Questions.Add(new Question(Console.ReadLine(), new List<(string, bool)>()));
                                        while (true)
                                        {
                                            Console.WriteLine($"Input answer (leave empty to continue): ");
                                            string answer = Console.ReadLine();
                                            if (string.IsNullOrWhiteSpace(answer)) break;
                                            Console.WriteLine($"It is true answer? (True or False): ");
                                            try { 
                                                bool ta = bool.Parse(Console.ReadLine());
                                                quiz.Questions[quiz.Questions.Count - 1].Answers.Add((answer, ta));
                                            }
                                            catch (Exception ex)
                                            {
                                                Console.WriteLine(ex.Message);
                                            }
                                        }
                                        Console.Clear();
                                    }
                                    List<Quiz> quizes = new List<Quiz>();
                                    if (File.Exists(quizList))
                                    {
                                        quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                                    }
                                    quizes.Add(quiz);
                                    File.WriteAllText(quizList, JsonConvert.SerializeObject(quizes));
                                    Console.WriteLine("You have successfully created a quiz!");
                                    Console.ReadKey(true);
                                    Console.Clear();
                                    break;
                                }
                            case 1:
                                //EDIT QUESTION
                                Console.Clear();
                                if (File.Exists(quizList))
                                {
                                    List<Quiz> quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                                    foreach (var item in quizes)
                                    {
                                        Console.WriteLine(item + "\n");
                                    }
                                    Console.WriteLine("Input name of quiz:");
                                    string qname = Console.ReadLine();
                                    int q = quizes.FindIndex(qu => qu.Name == qname);
                                    if (q == -1)
                                    {
                                        Console.WriteLine("Quize is not exist!");
                                    }
                                    else
                                    {
                                        Console.Clear();
                                        foreach (var item in quizes[q].Questions)
                                        {
                                            Console.WriteLine(item.Name + "\n");
                                        }
                                        Console.WriteLine("Input question for edit:");
                                        string qt = Console.ReadLine();
                                        int qi = quizes[q].Questions.FindIndex(qu => qu.Name == qt);
                                        if (q == -1)
                                        {
                                            Console.WriteLine("Question is not exist!");
                                        }
                                        else
                                        {
                                            Console.Clear();
                                            Console.WriteLine($"Input new question: ");
                                            quizes[q].Questions[qi].Name = Console.ReadLine();
                                            quizes[q].Questions[qi].Answers = new List<(string, bool)>();
                                            while (true)
                                            {
                                                Console.WriteLine($"Input answer (leave empty to continue): ");
                                                string answer = Console.ReadLine();
                                                if (string.IsNullOrWhiteSpace(answer)) break;
                                                Console.WriteLine($"It is true answer? (True or False): ");
                                                try
                                                {
                                                    bool ta = bool.Parse(Console.ReadLine());
                                                    quizes[q].Questions[qi].Answers.Add((answer, ta));
                                                }
                                                catch(Exception ex)
                                                {
                                                    Console.WriteLine(ex.Message);
                                                }
                                            }
                                            File.WriteAllText(quizList, JsonConvert.SerializeObject(quizes));
                                            Console.WriteLine("You have successfully edit a question!");
                                        }
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("Quizes not found :(");
                                }
                                Console.ReadKey(true);
                                Console.Clear();
                                break;
                            case 2:
                                //DELETE QUIZ
                                Console.Clear();
                                if (File.Exists(quizList))
                                {
                                    List<Quiz> quizes = JsonConvert.DeserializeObject<List<Quiz>>(File.ReadAllText(quizList));
                                    foreach (var item in quizes)
                                    {
                                        Console.WriteLine(item + "\n");
                                    }
                                    Console.WriteLine("Input name of quiz:");
                                    string qname = Console.ReadLine();
                                    int q = quizes.FindIndex(qu => qu.Name == qname);
                                    if (q == -1)
                                    {
                                        Console.WriteLine("Quize is not exist!");
                                    }
                                    else
                                    {
                                        Console.Clear();
                                        Console.ForegroundColor = ConsoleColor.Red;
                                        Console.WriteLine($"Are you shure, you wont to delete a quiz? (input yes to continue): ");
                                        Console.ForegroundColor = ConsoleColor.Gray;
                                        string shure = Console.ReadLine();
                                        if(shure.ToLower() == "yes")
                                        {
                                            quizes.RemoveAt(q);
                                            File.WriteAllText(quizList, JsonConvert.SerializeObject(quizes));
                                            Console.WriteLine("Quiz succefull deleted!");
                                        }
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("Quizes not found :(");
                                }
                                Console.ReadKey(true);
                                Console.Clear();
                                break;
                            case 3:
                                break;
                        }
                        Console.Clear();
                        break;

                    case 6:
                        //EXIT
                        return;
                }
            }
        }
    }
}
