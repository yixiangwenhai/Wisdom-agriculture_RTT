
Page({
  data: {
    phone: '',
    password:''
  },
 
// 获取输入账号
  phoneInput :function (e) {
    this.setData({
      phone:e.detail.value
    })
  },
 
// 获取输入密码
  passwordInput :function (e) {
    this.setData({
      password:e.detail.value
    })
  },
 
// 登录
  login: function () {
    if(this.data.phone == 'admin' && this.data.password == 'admin'){
      wx.redirectTo({
        url:'../mainwindows/mainwindows'
      })

}
else{
  wx.showToast({  
    title: '用户名和密码错误',  
    icon: 'loading',  
    duration: 1000  
  })          
    }  
  }
})

