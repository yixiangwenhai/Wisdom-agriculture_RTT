const app =getApp()
var mqtt = require('../../utils/mqtt.js')
var client = null
//let topic = `/sys/${deviceConfig.productKey}`
//let topic = `/sys/${deviceConfig.productKey}/${deviceConfig.deviceName}/thing/event/property/post`;
//var lightvalue=0,eco2value=0,tvocvalue=0,tempvalue=0,humvalue=0

Page({
  data: {
    lightvalue:0,
    eco2value:0,
    tvocvalue:0,
    tempvalue:0,
    humvalue:0,
    LEDstate: false,
    HUMstate: false,
    FENstate: false,
  },
  onLoad() {
  },
  connectMqtt:function(){
    var that=this
    const options ={
      connectTimeout:4000,
      clientId:'weixin'+Math.ceil(Math.random()*10),
      port:8084,
      username:'123',
      password:'456'
    }
    client = mqtt.connect('wxs://www.ouweimin.xyz/mqtt',options)
    client.on('connect',(e)=>{
      console.log('连接服务器成功')
      this.setData({
        state:'连接成功'
      })
      client.subscribe('a',{
        qos:1
      },function(err){
        if(!err){
          console.log('订阅 主题a 成功')
        }
      })
      client.subscribe('light',{
        qos:1
      },function(err){
        if(!err){
          console.log('订阅 主题light 成功')
        }
      })
      client.subscribe('eco2',{
        qos:1
      },function(err){
        if(!err){
          console.log('订阅 主题eco2 成功')
        }
      })
      client.subscribe('tvoc',{
        qos:1
      },function(err){
        if(!err){
          console.log('订阅 主题tvoc 成功')
        }
      })
      client.subscribe('temp',{
        qos:1
      },function(err){
        if(!err){
          console.log('订阅 主题temp 成功')
        }
      })
      client.subscribe('hum',{
        qos:1
      },function(err){
        if(!err){
          console.log('订阅 主题hum 成功')
        }
      })
    })
    client.on('message',function(topic,message){
      if(topic=='light'){
        that.setData({
          lightvalue:message.toString()
        })
      }
      else if(topic=='eco2'){
        that.setData({
          eco2value:message.toString()
        })
      }
      else if(topic=='tvoc'){
        that.setData({
          tvocvalue:message.toString()
        })
      }
      else if(topic=='temp'){
        that.setData({
          tempvalue:message.toString()
        })
      }
      else if(topic=='hum'){
        that.setData({
          humvalue:message.toString()
        })
      }
    })
    client.on('reconnect',(error)=>{
      console.log('正在重连',error)
    })    
    client.on('error',(error)=>{
      console.log('连接失败',error)
      this.setData({
        state:'连接失败'
      })
    })
  },

  connectservice(){
    this.connectMqtt()
  },

  changeLed(){if(!this.data.LEDstate){
      client.publish('a','LED_HIGH',function(err){
        if(!err)
          console.log("LED开启")
      }),
      this.setData(this.data.LEDstate=!this.data.LEDstate)
    }
    else{
      client.publish('a','LED_LOW',function(err){
        if(!err)
          console.log("LED关闭")
      })     
      this.setData(this.data.LEDstate=!this.data.LEDstate)
    }},    
    changeHum(){if(!this.data.HUMstate){
      client.publish('a','HUM_HIGH',function(err){
        if(!err)
          console.log("加湿器开启")
      })
      this.setData(this.data.HUMstate=!this.data.HUMstate)
    }
    else{
      client.publish('a','HUM_LOW',function(err){
        if(!err)
          console.log("加湿器关闭")
      })
      this.setData(this.data.HUMstate=!this.data.HUMstate)
    }},
    changeFen(){if(!this.data.FENstate){
      client.publish('a','FEN_HIGH',function(err){
        if(!err)
          console.log("风扇开启")
      })
      this.setData(this.data.FENstate=!this.data.FENstate)
    }
    else{
      client.publish('a','FEN_LOW',function(err){
        if(!err)
          console.log("风扇关闭")
      })
      this.setData(this.data.FENstate=!this.data.FENstate)
    }},  
})