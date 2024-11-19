using System;
using System.Collections;
using System.Collections.Generic;

// Клас Друкарське Видання
public class PrintEdition
{
    private string title; // Назва видання
    private int year;     // Рік видання

    public PrintEdition(string title, int year)
    {
        this.title = title;
        this.year = year;
    }

    public string Title
    {
        get { return title; }
        set { title = value; }
    }

        public int Year
    {
        get { return year; }
        set { year = value; }
    }

        public override string ToString()
    {
        return $"{Title} ({Year})";
    }
}

// Універсальний клас для роботи зі списком видань
public class GenericList<T> where T : PrintEdition
{
    private class Node
    {
        public Node Next { get; set; }
        public T Data { get; set; }

        public Node(T data)
        {
            Next = null;
            Data = data;
        }
    }

    private Node head;

    public GenericList()
    {
        head = null;
    }

    public void AddHead(T item)
    {
        Node newNode = new Node(item)
        {
            Next = head
        };
        head = newNode;
    }

    public IEnumerator<T> GetEnumerator()
    {
        Node current = head;

        while (current != null)
        {
            yield return current.Data;
            current = current.Next;
        }
    }

    public T FindByTitle(string title)
    {
        Node current = head;

        while (current != null)
        {
            // Обмеження дозволяє доступ до властивості Title
            if (current.Data.Title == title)
            {
                return current.Data;
            }
            current = current.Next;
        }

        return null;
    }
}

// Тестування реалізації
class Program
{
    static void Main()
    {
        // Створюємо список друкарських видань
        GenericList<PrintEdition> list = new GenericList<PrintEdition>();

        // Додаємо видання до списку
        list.AddHead(new PrintEdition("The Great Gatsby", 1925));
        list.AddHead(new PrintEdition("1984", 1949));
        list.AddHead(new PrintEdition("To Kill a Mockingbird", 1960));

        // Виводимо список видань
        Console.WriteLine("Список видань:");
        foreach(var edition in list)
        {
            Console.WriteLine(edition);
        }

        // Знаходимо видання за назвою
        string searchTitle = "1984";
        PrintEdition found = list.FindByTitle(searchTitle);
        if (found != null)
        {
            Console.WriteLine($"\nЗнайдено видання: {found}");
        }
        else
        {
            Console.WriteLine($"\nВидання з назвою '{searchTitle}' не знайдено.");
        }
    }
}
