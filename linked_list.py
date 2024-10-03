
# This is an implementation of the node of a singly linked list
class SinglyLinkedListNode:
    def __init__(self, node_data):
        """The class constructor

        Args:
            node_data (_type_): the data contained by the node
        """
        self.data = node_data
        # next is the next node connected to the actual node
        self.next = None     
        
    # method to print a node
    def __str__(self):
        return str(self.data)
    
# Class that implements a singly linked list
class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.length = 0

    def append(self, data):
        """adding a new node at the end of the list

        Args:
            data (int, float, str): the new data to insert as the last node

        Returns:
            SinglyLinkedList: it returns the updated list 
        """
        
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
        """Inserting a new node containing data at the list front

        Args:
            data (int, float, str): data to be inserted
        """
        old_node = self.head
        self.head = SinglyLinkedListNode(data)
        self.head.next = old_node
        self.length += 1
            
    def insertAt(self, position, data):
        """Inserting a new node at position position with the data data

        Args:
            position (int): the position where insert the data
            data (int, float, str): _description_
        """
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
    
    def pop(self):
        """Removing the last element of a linked list
        """
        assert self.length >0, "ERROR: you cannot remove an element from an empty linked list"
        
        previous_node = self.head
        for _ in range(self.length - 2):
            previous_node = previous_node.next
            
        previous_node.next = None
        self.length -= 1
    
    def deleteAt(self, position):
        """Removing the node at position

        Args:
            position (int): the position of the node to be deleted
        """
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
    
    def printInReverse(self):
        """
        Printing the list in reverse order
        """
        for i in reversed(range(0, self.length - 1)):
            print(self.__getitem__(i).data)
            
    def reverse(self):
        """
        Reversing the list
        """
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
        """the minimum function

        Returns:
            SinglyLinkedListNode: the node that contains the minimum value
        """
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
            
            return node_min
        
    def max(self):
        """the max function

        Returns:
             SinglyLinkedListNode: the node that contains the maximum value
        """
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
            
            return node_max
    
    def find(self, value):
        """Function that searches a value in the linked list and returns its position

        Args:
            value (int, float, str): the value to search for

        Returns:
            int: the value index. If the values is not present, it returns -1
        """
        index = -1
        if self.length == -1:
            return index
        
        for i in range(0, self.length):
            if self.__getitem__(i).data == value:
                index = i
                break
        return index
                   
    # method to copy a list 
    def copy(self):
        copied = SinglyLinkedList()
        for i in range(self.length):
            copied.append(self.__getitem__(i).data)
            
        return copied
    
    def sort(self):
        """Sorting the list in ascending order
        """
        sorted = SinglyLinkedList()
        copied = self.copy()
        while copied.length != 0:
            minimum = copied.min().data
            index = copied.find(minimum)
            sorted.append(minimum)
            copied.deleteAt(index)
            
        return sorted
    
    def unique(self):
        """Unique values

        Returns:
            SinglyLinkedList: list that contains the unique values from the linked list
        """
        if self.length == 0 or self.length == 1:
            return self.head
        
        myList = SinglyLinkedList()
        
        value = self.head.data
        myList.append(value)
        actual_node = self.head
        
        copied = self.copy()
        while True:
            # loop that removes all the occurrence of value
            while copied.find(value) != -1:
                copied.deleteAt(copied.find(value))
            
           
            if copied.length ==0:
                return myList
            
            actual_node=copied.head
            value = actual_node.data
            myList.append(value)
            
            
        
    
    def __getitem__(self, index: int):
        """
        Accessing self[index]
        Args:
            index (int): index of the selected node inside the list

        Returns:
            SinglyLinkedListNode: selected node of the list
        """
        assert index < self.length, "ERROR: index out of range"
        
        node = self.head
        for _ in range(index):
            node = node.next
        
        return node
            
    
    def __len__(self):
        """Implementing the len method

        Returns:
            int: length of the linked list
        """
        return self.length
    
    def __str__(self):
        """Implementing the print(self) method

        Returns:
            str: a human-readable string that represents the list
        """
        my_string='['
        for i in range(self.length):
            my_string+= str(self.__getitem__(i).data)
            
            if i != self.length- 1:
                my_string+=', '
                
        return my_string + ']'
    
    # overloading the + method
    def __add__(self, other):
        """_summary_

        Args:
            other (SinglyLinkedList): the other linked list to be added to self

        Returns:
            SinglyLinkedList: the sum list
        """
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
        
                
if __name__ == '__main__':
     
    # 1. Instance and appending some values
    llist = SinglyLinkedList()
    
    llist_count = 3

    for i in range(llist_count):
        llist_item = 3
        llist.append(llist_item)
        
    print(llist)
    
    
    # 2. Appending some values and finding the unique values
    
    llist.append(0)
    llist.append(5)
    llist.append(8)
    llist.append(0)
    llist.append(5)
    llist.append(5)
    
    
    print(llist)
    
    
    
    unique_values = llist.unique()
    print(unique_values)
    

    # 3. Inserting some data and finding the max
    llist.insertAtFront(30)
    llist.insertAtFront(40)
    llist.insertAtFront(10)
    print(llist)
    
    # 4. Printing the max of the linked list
    print(llist.max())
    
    # 5. Sorting the list
    sorted = llist.sort()
    print(sorted)
        

