//
//  SwiftLinkList.swift
//  Sort
//
//  Created by le on 2018/7/20.
//  Copyright © 2018年 le. All rights reserved.
//

import UIKit

public class LinkListNode <T> {
    var value : T
    var next : LinkListNode ?
    weak var previous : LinkListNode ?
    
    public init(value : T) {
        self.value = T
    }
}

public class LinkedList <T> {
    public typealias Node = LinkListNode<T>
    
    private var head : Node ?
    
    public var isEmpty : Bool {
        return head == nil
    }
    public var first : Node ? {
        return head
    }
    
    public var last : Node ? {
        guard var node = head else {
            return nil
        }
        while let next = node.next {
            node = next
        }
        return node
    }
    
    
    public func append(value : T) {
        let newNode = Node(value: T)
        if let lastNode = last {
            newNode.previous = lastNode
            lastNode.next = newNode
        }else {
            head = newNode
        }
    }
}
