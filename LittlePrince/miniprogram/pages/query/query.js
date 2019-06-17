// miniprogram/pages/course/query/query.js
const app = getApp()
Page({
    /**
     * 页面的初始数据
     */
    db: undefined,
    course: undefined,
    data: {
      nameIn: '',
      roomResult: '',
      scheduleResult: ''
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this
    //  调用login云函数获取openid
    wx.cloud.callFunction({
      name: 'login',
      data: {},
      success: res => {
        console.log('[云函数] [login] user openid: ', res.result.openid)
        app.globalData.openid = res.result.openid
        wx.cloud.init({ env: 'jim72zhou' })
        that.db = wx.cloud.database()
        that.course = that.db.collection('course')
      },
      fail: err => {
        console.error('[云函数] [login] 调用失败', err)
        wx.navigateTo({
          url: '../deployFunctions/deployFunctions',
        })
      }
    })
  },
  
  //  单击“查询数据”按钮执行该函数
  queryData: function () {
    var that = this
    //  搜索数据集  
    this.db.collection('course').where({
      student: that.data.nameIn
    })
      .get({
        success : function(res) {
          if (res.data.length > 0) {
            console.log(res.data),
            that.setData({
              roomResult: res.data[0].room,
              scheduleResult: res.data[0].schedule
            })
          }
          else{
            that.setData({
              roomResult: '',
              scheduleResult: ''
            })
            wx.showModal({
              title: '没有你要的数据',
              content: '请检查查询条件！',
              showCancel: false
            })
          }
        },
        fail: function(res) {
          wx.showModal({
            title: '查询失败',
            content: '没有你要的数据！',
            showCancel: false
          })
        }
      })
  },
  
  bindKeyInputNameIn: function (e) {
    this.setData({
      nameIn: e.detail.value
    })
  },
})