//
//  ViewController.swift
//  DataLearn
//
//  Created by le on 2018/7/20.
//  Copyright © 2018年 le. All rights reserved.
//

import UIKit


class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        let list = LinkedList<String>()
        list.isEmpty
        list.first
        list.appendLinkList(value: "hello")
        list.appendLinkList(value: "sb")
        
        let Node = list.node(atIndex: 0)
        print(Node.value)
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}



