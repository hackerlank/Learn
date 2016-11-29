// =====================================================================================
//
//       Filename:  BoostObject.h
//
//    Description:  可以加速的对象
//
//        Version:  1.0
//        Created:  01/21/2015 08:57:54 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef BOOST_OBJECT_H
#define BOOST_OBJECT_H

enum EBoostObjectType // 加速对象类型
{
    eBOTNone = 0,
    eBOTUser,
    eBOTPlayer,
    eBOTFighter,
    eBOTPlayerFighter,
    eBOTHeroFighter,
    eBOTTrump,
    eBOTPet,
    eBOTMax
};

// =====================================================================================
//        Class:  CBoostObject
//  Description:  加速对象
// =====================================================================================
class CBoostObject
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBoostObject ();                             // constructor //
        virtual ~CBoostObject ();

        // ====================  ACCESSORS     ======================================= //
        virtual EBoostObjectType GetType() const = 0;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        virtual void Super() {};

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //

}; // -----  end of class CBoostObject  ----- //

#endif // #ifndef BOOST_OBJECT_H

