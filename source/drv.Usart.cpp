/**
 * @file      drv.Usart.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "drv.Usart.hpp"
#include "drv.UsartController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace drv
{
    
static UsartController* getController()
{
    static UsartController* controller( NULLPTR );    
    if( controller == NULLPTR )
    {
        controller = new UsartController;
        if( controller != NULLPTR )
        {
            if( !controller->isConstructed() )
            {
                delete controller;
                controller = NULLPTR;                
            }
        }
    }
    return controller;
}
    
Usart* Usart::create(SerialLineConfig const& config)
{
    lib::UniquePointer<Usart> res;
    UsartController* const controller( getController() );
    if( controller != NULLPTR )
    {    
        res.reset( controller->createResource(config) );
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {
                res.reset();
            }
        }
    }
    return res.release();
}

Usart::~Usart(){}

} // namespace drv
} // namespace eoos
