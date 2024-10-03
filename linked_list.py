#!/bin/python3

import math
import os
import random
import re
import sys

class SinglyLinkedListNode:
    def __init__(self, node_data):
        self.data = node_data
        self.next = None
        
    def __str__(self):
        return str(self.data)
    
    # def __add__(self, other):
    #     if not(isinstance(other)

class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.length = 0

    @staticmethod
    def print_singly_linked_list(node, sep):
        while node:
            print(str(node.data), end='')

            node = node.next

            if node:
                print(sep, end='')


    def append(self, data):
        
        if not(isinstance(data, int)) and not(isinstance(data, str)) and not(isinstance(data, float)):
            print("ERROR: You can append only integers, strings, or floating numbers")
            exit(-1)

        if self.head is None:
            self.head = SinglyLinkedListNode(data)
            self.length = 1
            return self.head

        last_node = self.__getitem__(self.length - 1)
        last_node.next = SinglyLinkedListNode(data)
        self.length += 1
        return self
            
    def insertAtFront(self, data):
        old_node = self.head
        self.head = SinglyLinkedListNode(data)
        self.head.next = old_node
        self.length += 1
            
    def insertAt(self, position, data):
        assert position < self.length, "ERROR: the insertion position is greater than the linked list length"
        
        assert position > 0, "ERROR: the insertion position cannot be a negative number"
        
        if position == 0:
            self.insertAtFront(data)
            return
            
        previous_node = self.__getitem__(position - 1)
        old_node = self.__getitem__(position)
        
        inserted_node = SinglyLinkedListNode(data)
        inserted_node.next = old_node
        previous_node.next = inserted_node
        self.length += 1
        return
    
    def pop(self):
        assert self.length >0, "ERROR: you cannot remove an element from an empty linked list"
        
        previous_node = self.head
        for i in range(self.length - 2):
            previous_node = previous_node.next
            
        previous_node.next = None
        self.length -= 1
        return
    
    def deleteAt(self, position):
        assert position < self.length, "ERROR: the delete position is greater than the linked list length"
        
        if self.length == 1:
            self.head = None
            self.length = 0
            return
        
        # Removing the first element
        if position == 0:
            self.head = self.__getitem__(1)
            self.length -= 1
            return
        
        previous_node = self.head
        for _ in range(position - 1):
            previous_node = previous_node.next
         
        node_to_delete = previous_node.next   
        previous_node.next = node_to_delete.next
        
        self.length -= 1
        return
    
    # maybe it is better as a static method
    def printInReverse(self):
        print("reversed")
        for i in reversed(range(0, self.length - 1)):
            print(self.__getitem__(i).data)
            
    def reverse(self):
        if self.length == 0 or self.length == 1:
            return self.head
        
        new_head = None
        for i in reversed(range(0, self.length)):
            if i == self.length - 1:
                new_head = self.__getitem__(i)
                new_head.next = self.__getitem__(i - 1)
            elif i == 0:
                node = self.__getitem__(i)
                node.next = None
            else:
                node = self.__getitem__(i)
                node.next = self.__getitem__(i-1)
            
        self.head = new_head
        return
    
    def min(self):
        if self.length == 0:
            return None
        elif self.length == 1:
            return self.head
        else:
            min = self.head.data
            node_min = self.head
            for i in range(self.length):
                if min > self.__getitem__(i).data:
                    min = self.__getitem__(i).data
                    node_min = self.__getitem__(i)
            
            # print(min) 
            return node_min
        
    def max(self):
        if self.length == 0:
            return None
        elif self.length == 1:
            return self.head
        else:
            max = self.head.data
            node_max = self.head
            for i in range(0, self.length):
                if max < self.__getitem__(i).data:
                    max = self.__getitem__(i).data
                    node_max = self.__getitem__(i)
            
            # print(max) 
            return node_max
    
    # Function that searches a value in the linked list and returns its position
    # If the values is not present, it returns -1
    def find(self, value):
        index = -1
        if self.length == -1:
            return index
        
        for i in range(0, self.length):
            if self.__getitem__(i).data == value:
                index = i
                break
        return index
                    
    def sort(self):
        sorted = SinglyLinkedList()
        while self.length != 0:
            minimum = self.min().data
            index = self.find(minimum)
            sorted.append(minimum)
            self.deleteAt(index)
            print("The minimum", minimum)
            print("The index", index)
            print("The unsorted list", self)
            print("The sorted list", sorted)
            
        return sorted
    
    # function that returns a linked list withoud duplicated values
    def unique(self):
        if self.length == 0 or self.length == 1:
            return self.head
        
        myList = SinglyLinkedList()
        
        value = self.head.data
        myList.append(value)
        actual_node = self.head

        while True:
            # loop that removes all the occurrence of value
            while self.find(value) != -1:
                self.deleteAt(self.find(value))    
            
            
            if self.length ==0:
                return myList
            
            actual_node=self.head
            value = actual_node.data
            myList.append(value)
            
            
        
    
    def __getitem__(self, index):
        assert index < self.length, "ERROR: index out of range"
        
        node = self.head
        for _ in range(index):
            node = node.next
        
        return node
            
    
    def __len__(self):
        return self.length
    
    def __str__(self):
        my_string='['
        for i in range(self.length):
            my_string+= str(self.__getitem__(i).data)
            
            if i != self.length- 1:
                my_string+=', '
                
        return my_string + ']'
    
    # overloading the + method
    def __add__(self, other):
        if isinstance(other, SinglyLinkedList):
            last_node = self.__getitem__(self.length - 1)
            last_node.next = other.head
            self.length += other.length
            return self
        elif isinstance(other, int) or isinstance(other, float) or isinstance(other, str):
            return self.append(other)
        else:
            print("ERROR: you can add only an other single linked list, a float, an integer or a string")
            exit(-1)
        
    
# function that returns the length of a li     
def length(llist):
    l = 0
    
    node = llist
    while node:
        l += 1
        node = node.next
    
    return l

# function that returns the selected node
def selectNode(llist, index):
    l = length(llist)
    assert index < l, "ERROR: the deletion index is greater than the linked list dimension"
    
    node = llist
    for i in range(index):
        node = node.next
        
    return node

    
            
if __name__ == '__main__':
     

    llist = SinglyLinkedList()
    
    llist_count = 10

    for i in range(llist_count):
        llist_item = 3
        llist.append(llist_item)
        
    llist.append(4)
    llist.append(4)
    llist.append(4)
    
    llist.append(5)
    
    llist.append(0)
    llist.append(35)
    llist.append(10)
    llist.append(0)
    llist.append(7)
    llist.append(35)
    
    
    print(llist)
    
    
    a = llist.unique()
    print(a)

    # llist.insertAtFront(30)
    # llist.insertAtFront(40)
    # llist.insertAtFront(10)
    # print(llist)
    
    # print(llist.max())
    # a = llist.sort()
        
    # print(llist.find(1000))
    # a = llist.sort()
    # llist.deleteAt(len(llist) - 1)
    # print(llist)
    # llist = llist + 5
    # print(llist)
    # llist.min()
    
    # SinglyLinkedList.print_singly_linked_list(llist.head, '\n')
    
    # print('\n')
    
    # print(llist)
    
    
    # # llist.printInReverse()
    # llist.reverse()
    
    
    # SinglyLinkedList.print_singly_linked_list(llist.head, '\n')
    # print("\n")
    # print(len(llist))
    
    # print("\n\n")
    
    # llist.deleteAt(3)
    # SinglyLinkedList.print_singly_linked_list(llist.head, '\n')
    # print("\n")
    # print(len(llist))

    # print(length(llist.head))
    
    # print(selectNode(llist.head, 2).data)
    
    # l2 = SinglyLinkedList()
    # l2.append(5)
    # l2.append(6)
    # l2.append(100)
    
    
    
    # l3 = llist + l2
    # print(l3)
