//
//  Store.swift
//  MVC
//
//  Created by le on 2018/10/24.
//  Copyright © 2018年 le. All rights reserved.
//

import Foundation

final class Store: NSObject {
    static let changedNotification = Notification.Name("StoreChanged")
    static private let documentDirectory = try! FileManager.default.url(for: .libraryDirectory, in: .userDomainMask, appropriateFor: nil, create: true)
    static let shared = Store(url: documentDirectory)
    
    let baseURL: URL?
    var placeholder: URL?
    
//    private(set) var rootFolder: Folder
//    init (url: URL?) {
//        self.baseURL = url
//        self.placeholder = nil
//
//        if let u = url,
//            let data = try? Data(contentsOf: u.appendingPathComponent(.storLocation)),
//            let folder = try? JSONDecoder().decode(Floder.self, from: data)
//
//    }
    
    
}
