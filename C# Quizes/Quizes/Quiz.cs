using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Quizes
{
    class Quiz
    {
        public string Name { get; set; }
        public string Subject { get; set; }
        public string Creator { get; set; }
        public List<(int, string)> ScoreBoard { get; set; } = new List<(int, string)>();
        private int mark = 0;
        public List<Question> Questions { get; set; } = new List<Question>();

        public Quiz() { }
        public Quiz(string name, string subject, string creator)
        {
            Name = name;
            Subject = subject;
            Creator = creator;
        }
        public override string ToString()
        {
            return $"{Subject}:{Name}\nCreated by {Creator}";
        }

        public void Start(string name)
        {
            Random rnd = new Random();
            int i = 0;
            while (i < Questions.Count)
            {
                int r = rnd.Next(0, Questions.Count);
                if (Questions[r].mark == -1)
                {
                    Console.Write((i + 1) + "/" + Questions.Count + " ");
                    mark += Questions[r].Ask();
                    i++;
                    Console.Clear();
                }
            }
            for (int q = 0; q < Questions.Count; q++)
            {
                Questions[q].mark = -1;
            }
            int position = ScoreBoard.FindIndex(sb => sb.Item1 < mark);
            int uposition = ScoreBoard.FindIndex(sb => sb.Item2 == name);
            if(uposition != -1 && ScoreBoard[uposition].Item1 < mark)
            {
                ScoreBoard.RemoveRange(uposition, 1);
                uposition = -1;
            } 
            if (uposition == -1)
            {
                if (position != -1)
                    ScoreBoard.Insert(position, (mark, name));
                else
                    ScoreBoard.Add((mark, name));
            }
            Console.WriteLine($"Your mark: {mark}/{Questions.Count}\n");
            Console.WriteLine($"Your position in Score board: {((position == -1) ? (ScoreBoard.Count) : (position + 1))}");
        }
        public void ScoreBoardPrint()
        {
            Console.ForegroundColor = ConsoleColor.Green;
            for (int i = 0; i < 20 && i < ScoreBoard.Count; i++)
            {
                Console.WriteLine($"{i + 1}. {ScoreBoard[i].Item2}: {ScoreBoard[i].Item1,-6}");
                Console.ForegroundColor = ConsoleColor.DarkYellow;
            }
            Console.ForegroundColor = ConsoleColor.Gray;
        }
    }



    class Question
    {
        public string Name { get; set; }
        public List<(string, bool)> Answers { get; set; }
        public short mark { get; set; } = -1;
        public Question() { }
        public Question(string name, List<(string, bool)> answers)
        {
            Name = name;
            Answers = answers;
        }
        public int Ask()
        {
            Console.WriteLine($"{Name}:");
            string correct = "";
            for(short i = 0; i < Answers.Count; i++)
            {
                Console.WriteLine($"{(char)(i + 'A')}. {Answers[i].Item1}");
                if (Answers[i].Item2)
                {
                    if (correct != "") correct += " ";
                    correct += (char)(i + 'A');
                }
            }
            Console.WriteLine("\nInput answer like: A B C");
            Console.Write("Answer: ");
            string answer = Console.ReadLine().ToUpper();
            if (answer == correct) mark = 1;
            else mark = 0;
            return mark;
            //Console.WriteLine(mark);
        }
    }
}
