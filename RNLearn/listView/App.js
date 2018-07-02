/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 * @flow
 */

import React, { Component } from 'react';
import {
  Platform,
  StyleSheet,
  Text,
  View,
  ListView,
  TextInput,
} from 'react-native';

const instructions = Platform.select({
  ios: 'Press Cmd+R to reload,\n' +
    'Cmd+D or shake for dev menu',
  android: 'Double tap R on your keyboard to reload,\n' +
    'Shake or press menu button for dev menu',
});

export default class App extends Component<Props> {

  constructor(props) {
    super(props);

    const ds = new ListView.DataSource({rowHasChanged:(r1,r2) => r1 != r2});

    this.state = {
      dataSource: ds.cloneWithRows(['row1','row2']),
    };
  }


  render() {
    return (
      <ListView
        style = {{flex:1,marginTop:20,backgroundColor:'#F5FCFF'}}
        dataSource = {this.state.dataSource}
        renderRow = {(data) => 
          <View style={{height:50,backgroundColor:'white'}}>
            <Text style={{marginLeft:15,height:20,backgroundColor:'white',marginTop:15,fontSize:14}}>{data}
            </Text>
          </View>}
        renderSeparator={(sectionId,rowId) => <View key={rowId} style={styles.separator} />}
        renderHeader={() => <Header/>}
      />
    );
  }
}

const Header = (props) => (
    <View style={styles.container}>
      <TextInput 
        style={styles.input}
        placeholder="Search..."
        onChangeText={(text) => console.log('search for',text)}
      />
    </View>
);

const styles = StyleSheet.create({
  container:{
    flex: 1,
    marginTop:20,
    backgroundColor: '#F5FCFF',
  },
  welcome:{
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions:{
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
  separator: {
    flex: 1,
    height: StyleSheet.hairlineWidth,
    backgroundColor: '#8E8E8E',
  },
  input: {
    height: 30,
    flex: 1,
    paddingHorizontal :8,
    fontSize : 15,
    backgroundColor : '#FFFFFF',
    borderRadius : 2,
  }
});
