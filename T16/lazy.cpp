template <typename V, typename F>
auto operator | ( const V& v, F func ) {
    if constexpr( is_same_v< bool, invoke_result_t< F, decltype( *begin( v ) ) > > ) {
        vector< decay_t< decltype( *begin( v ) ) > > res;
 
	for( auto x: v )
            if( invoke( func, x ) )
                res.push_back( x );

        return res;
    }
    else if constexpr( is_same_v< void, invoke_result_t< F, decltype( *begin( v ) ) > > ) {
        for( auto x: v )
            func( x );
    }
    else {
        vector< decay_t< invoke_result_t< F, decltype( *begin( v ) ) > > > res;
        
        for( auto x: v )
            res.push_back( invoke( func, x ) );
            
        return res;
    }  
}
