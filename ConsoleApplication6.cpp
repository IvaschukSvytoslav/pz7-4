using System;
using System.Collections;
using System.Collections.Generic;

// ���� ���������� �������
public class PrintEdition
{
    private string title; // ����� �������
    private int year;     // г� �������

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

// ������������ ���� ��� ������ � ������� ������
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
            // ��������� �������� ������ �� ���������� Title
            if (current.Data.Title == title)
            {
                return current.Data;
            }
            current = current.Next;
        }

        return null;
    }
}

// ���������� ���������
class Program
{
    static void Main()
    {
        // ��������� ������ ����������� ������
        GenericList<PrintEdition> list = new GenericList<PrintEdition>();

        // ������ ������� �� ������
        list.AddHead(new PrintEdition("The Great Gatsby", 1925));
        list.AddHead(new PrintEdition("1984", 1949));
        list.AddHead(new PrintEdition("To Kill a Mockingbird", 1960));

        // �������� ������ ������
        Console.WriteLine("������ ������:");
        foreach(var edition in list)
        {
            Console.WriteLine(edition);
        }

        // ��������� ������� �� ������
        string searchTitle = "1984";
        PrintEdition found = list.FindByTitle(searchTitle);
        if (found != null)
        {
            Console.WriteLine($"\n�������� �������: {found}");
        }
        else
        {
            Console.WriteLine($"\n������� � ������ '{searchTitle}' �� ��������.");
        }
    }
}
