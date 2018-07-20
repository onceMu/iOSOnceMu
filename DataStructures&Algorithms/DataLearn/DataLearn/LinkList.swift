//
//  LinkList.swift
//  DataLearn
//
//  Created by le on 2018/7/20.
//  Copyright © 2018年 le. All rights reserved.
//

import UIKit

class LinkList: NSObject {

}


//定义链表数据结构
public class LinkListNode <T> {
    var value: T
    var next: LinkListNode?
    weak var previous: LinkListNode?
    
    public init(value: T) {
        self.value = value
    }
}



public class LinkedList<T> {
    public typealias Node = LinkListNode<T>
    
    private var head: Node?
    
    public var isEmpty: Bool {
        return head == nil
    }
    
    //找到链表头结点
    public var first: Node? {
        return head
    }
    
    public var last: Node? {
        guard var node = head else {
            return nil
        }
        
        while let next = node.next {
            node = next
        }
        return node
    }
    
    
    public func appendLinkList(value: T) {
        let newNode = Node(value: value)
        if let lastNode = last {
            newNode.previous = lastNode
            lastNode.next = newNode
        }else {
            head = newNode
        }
    }
    
    public var count : Int {
        guard var node = head else {
            return 0
        }
        var count = 1
        while let next = node.next {
            node = next
            count += 1
        }
        return count
    }
    
    public func node(atIndex index : Int) -> Node {
        if index == 0 {
            return head!
        }else {
            var node = head!.next
            for _ in 1..<index {
                node = node?.next
                if node == nil {
                    break
                }
            }
            return head!
        }
    }
    
    public func insert(_ node: Node, atIndex index: Int) {
        let newNode = node
        if index == 0 {
            newNode.next = head
            head?.previous = newNode
            head = newNode
        }else {
            let prev = self.node(atIndex: index-1)
            let next = prev.next
            newNode.previous = prev
            newNode.next = prev.next
            prev.next = newNode
            next?.previous = newNode
        }
    }
    
    
}
































