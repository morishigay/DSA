# Now let's apply the concept of AVL Tree! First, we will be inserting the following nodes in order: 10, 20, 30, 5, 4, 15, 25, 35, 27, 26. 
# Then, we will delete all of them in the following order: 4, 5, 10, 15, 20, 25, 26, 27, 30, 35

# AVL tree node structure and its creation
class Node:
    def __init__(self, key):
        self.key = key
        self.left = self.right = None
        self.height = 1

# AVL tree structure and its operations
class AVLTree:
    def height(node):
        if not node:
            return 0
        return node.height
    
    def rightRotate(self, y):
        x = y.left
        t2 = x.right

        x.right = y
        y.left = t2

        y.height = 1 + max(self.height(y.left), self.height(y.right))
        x.height = 1 + max(self.height(x.left), self.height(x.right))
        return x
    
    def leftRotate(self, x):
        y = x.right
        t2 = y.left
        
        y.left = x
        x.right = t2

        x.height = 1 + max(self.height(x.left), self.height(x.right))
        y.height = 1 + max(self.height(y.left), self.height(y.right))
        return y
    
    def balance(self, node):
        if not node:
            return 0
        return self.height(node.left) - self.height(node.right)
    
    def insert(self, node, key):
        #usual bst insertion
        if not node:
            return Node(key)
        
        if key < node.key:
            node.left = self.insert(node.left, key)
        elif key > node.key:
            node.right = self.insert(node.right, key)
        else:
            return node
        
        #update height
        node.height = 1 + max(self.height(node.left), self.height(node.right))

        #get balance
        balance = self.balance(node)

        #if not balanced, there will be 4 cases
        #1. LL case
        if balance > 1 and key < node.left.key:
            return self.rightRotate(node)
        
        #2. RR case
        if balance < -1 and key > node.right.key:
            return self.leftRotate(node)
        
        #3. LR case
        if balance > 1 and key > node.left.key:
            node.left = self.leftRotate(node)
            return self.rightRotate(node)

        #4. RL case
        if balance < -1 and key < node.right.key:
            node.right = self.rightRotate(node)
            return self.leftRotate(node)
        
        return node
    
    def minValNode(self, node):
        curr = node
        while curr.left is not None:
            curr = curr.left
        return curr
    
    def remove(self, node, key):
        #usual BST deletion
        if not node:
            return node
        
        if key < node.key:
            node.left = self.remove(node.left, key)
        elif key > node.key:
            node.right = self.remove(node.right, key)
        else:
            if node.left is None or node.right is None:
                temp = node.left if node.left is not None else node.right
                if temp is None:
                    temp = node
                    node = None
                else:
                    node = temp
            else:
                temp = self.minValNode(node.right)
                node.key = temp.key
                node.right = self.remove(node.right, temp.key)
        
        if node is None:
            return node
        
        #update height
        node.height = 1 + max(self.height(node.left), self.height(node.right))

        #get balance
        balance = self.balance(node)

        #if not balanced there will be 4 cases
        #1. LL case
        if balance > 1 and self.balance(node.left) >= 0:
            return self.rightRotate(node)
        #2. RR case
        if balance < -1 and self.balance(node.right) <= 0:
            return self.leftRotate(node)
        #3. LR case
        if balance > 1 and self.balance(node.left) < 0:
            node.left = self.leftRotate(node.left)
            return self.rightRotate(node)
        #4. RL case
        if balance < -1 and self.balance(node.right) > 0:
            node.right = self.rightRotate(node.right)
            return self.leftRotate(node)
        
        return node